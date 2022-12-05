extends StaticBody2D

export var jump_multiplication_effect = 1

var direction = Vector2.RIGHT
var speed = 30

var velocity = Vector2.ZERO

func _physics_process(delta):
	var collision = move_and_collide(speed * direction * delta)
	if collision:
		velocity.y = -jump_impulse * collision.collider.jump_multiplication_effect	
	
	# screen wrapping
	var left_border = 0
	var right_border = get_viewport_rect().size.x
	if position.x < left_border:
		position.x = right_border
	elif position.x > right_border:
		position.x = left_border

