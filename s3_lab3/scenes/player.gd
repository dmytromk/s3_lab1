extends KinematicBody2D

export var jump_impulse : float = 5.5 * 60
export var gravity_impulse : float = 7.0 * 60
export var speed : float = 1 * 60

var velocity = Vector2.ZERO

var game_over = false
var left_border = 0
var right_border = 0

func _ready():
	right_border = get_viewport_rect().size.x

func _physics_process(delta):
	velocity += (Vector2.DOWN * gravity_impulse * delta)
	
	if Input.is_action_pressed("move_left"):
		velocity.x -= speed
	if Input.is_action_pressed("move_right"):
		velocity.x += speed
	velocity.x = lerp(velocity.x, 0, 0.2) #smoothes transition between "moving" and "stopping" (key is not pressed)
		
	var collision = move_and_collide(velocity * delta)
	if collision:
		if collision.collider.is_in_group("platform"):
			AudioStreamManager.play("res://assets/jump.wav")
		velocity.y = -jump_impulse * collision.collider.jump_multiplication_effect	
		
	
	# screen wrapping
	if position.x < left_border:
		position.x = right_border
	elif position.x > right_border:
		position.x = left_border

func die():
	AudioStreamManager.play("res://assets/pada.mp3")
	velocity = Vector2.ZERO
	set_collision_mask_bit(1, false)
