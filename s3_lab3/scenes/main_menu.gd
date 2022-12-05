extends Control

onready var highscore_label = $VBoxContainer/highscore

func _ready():
	var highscore = Global.read_savegame()
	highscore_label.text = "Current record\n" + str(int(highscore))

func _on_start_pressed():
	get_tree().change_scene("res://scenes/world.tscn")

func _on_exit_pressed():
	get_tree().quit()
