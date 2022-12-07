extends KinematicBody2D

export var move_speed = 200.0

var velocity := Vector2.ZERO

var jump_height : float = 140
var jump_time_to_peak : float = 0.9 / Global.insane_mode
var jump_time_to_descent : float = 0.9 / Global.insane_mode

var speed_x : float = 60 * Global.insane_mode

var jump_velocity : float = ((2.0 * jump_height) / jump_time_to_peak) * -1.0
var jump_gravity : float = ((-2.0 * jump_height) / (jump_time_to_peak * jump_time_to_peak)) * -1.0
var fall_gravity : float = ((-2.0 * jump_height) / (jump_time_to_descent * jump_time_to_descent)) * -1.0

var game_over = false
var left_border = 0
var right_border = 0

func _ready():
  right_border = get_viewport_rect().size.x

func _physics_process(delta):
	velocity.y += fall_gravity * delta
	
	if Input.is_action_pressed("move_left"):
		velocity.x -= speed_x
	if Input.is_action_pressed("move_right"):
		velocity.x += speed_x
	velocity.x = lerp(velocity.x, 0, 0.2) #smoothes transition between "moving" and "stopping" (key is not pressed)
	
	var collision = move_and_collide(velocity * delta)
	
	if collision:
		if collision.collider.is_in_group("platform"):
			AudioStreamManager.play("res://assets/jump.wav")
			
		elif collision.collider.is_in_group("enemy"):
			AudioStreamManager.play("res://assets/jump_monster.mp3")
			
		velocity.y = jump_velocity * collision.collider.jump_multiplication_effect      
			
	# screen wrapping
	if position.x < left_border:
		position.x = right_border
	elif position.x > right_border:
		position.x = left_border

func jump():
	velocity.y = jump_velocity

func die():
	AudioStreamManager.play("res://assets/pada.mp3")
	velocity = Vector2.ZERO
	set_collision_mask_bit(1, false)
