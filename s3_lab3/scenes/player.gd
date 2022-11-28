extends KinematicBody2D

export var jump_impulse : float = 400
export var gravity_impulse : float = 10
export var speed : float = 3.0 * 60

var score = 0 #also traveled y-distance

var velocity = Vector2.ZERO

onready var camera = get_node('../Camera2D')
var game_over = false

func _physics_process(delta):
	if game_over:
		return
	
	velocity += (Vector2.DOWN * gravity_impulse * delta)
	
	if Input.is_action_pressed("move_left"):
		velocity.x -= speed
	if Input.is_action_pressed("move_right"):
		velocity.x += speed
	velocity.x = lerp(velocity.x, 0, 0.2) #smoothes transition between "moving" and "stopping" (key is not pressed)
	
	if is_on_floor():
		velocity += (Vector2.UP * jump_impulse)
		
	move_and_slide(velocity, Vector2.UP)
	
	# screen wrapping
	if position.x < 0:
		position.x = get_viewport_rect().size.x
	elif position.x > get_viewport_rect().size.x:
		position.x = 0
		
	# score system
	if position.y < score:
		score = position.y
		camera.position.y = position.y
	
	if (-score) - (-position.y) > 0:
		game_over = true
