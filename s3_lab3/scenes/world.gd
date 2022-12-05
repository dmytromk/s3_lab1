extends Node2D

onready var player = $player
onready var camera = $Camera2D
onready var score_label = $Camera2D/score
onready var platform_generator = $platform_generator

onready var intital_camera_position_y = $Camera2D.position.y
onready var intital_platform_position_y = $platform_generator/platform.position.y - 30

var score: = 0
var highscore = Global.read_savegame()

export(Array, PackedScene) var platform_scene

func world_generation(plaforms_amount):
	var last_platform_is_enemy = false
	for i in plaforms_amount:
		intital_platform_position_y -= rand_range(50, rand_range(70, min(120, 70 + score/100)))
		
		var new_platform
		var platform_type = randi()%10 # 0 - booster, else - standatd
		
		if platform_type == 0:
			new_platform = platform_scene[1].instance() as RigidBody2D
		elif platform_type >= 1 and platform_type <= 2 and last_platform_is_enemy == false and score > 200:
			new_platform = platform_scene[2].instance() as StaticBody2D
			last_platform_is_enemy = true
		else:
			new_platform = platform_scene[0].instance() as RigidBody2D
			
		if new_platform != null:
			new_platform.position = Vector2(rand_range(20, 160), intital_platform_position_y)
			platform_generator.call_deferred("add_child", new_platform)
	
func _ready():
	randomize()
	world_generation(20)

func _physics_process(delta):
	var pla = player.position.y 
	var cam = camera.position.y
	if player.position.y < camera.position.y:
		score_update()
		camera.position.y = player.position.y


func delete_object(target):
	if target.is_in_group("player"):
		if score > highscore:
			Global.save(score)
		get_tree().change_scene("res://scenes/main_menu.tscn")
		
	else:
		target.queue_free()
		world_generation(1)
		
func _on_platform_eraser_body_entered(body):
	delete_object(body)

func score_update():
	score = intital_camera_position_y - camera.position.y
	score_label.text = "Score: " + str(int(score))
