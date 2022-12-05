extends StaticBody2D

export var jump_multiplication_effect = 1

var direction = Vector2.RIGHT
var speed = 80

var velocity = Vector2.ZERO
var right_border = 0

func _ready():
	right_border = get_viewport_rect().size

func _physics_process(delta):
	velocity = direction * speed
	position += velocity * delta
	if position >= right_border:
		direction *= -1
	elif position.x <= 0:
		direction *= -1

func _on_Area2D_body_entered(body):
	if body.is_in_group("player"):
		body.die()
