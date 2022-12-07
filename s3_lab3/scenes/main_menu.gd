extends Control

onready var highscore_label = $VBoxContainer/highscore

func _ready():
	Global.insane_mode = 1
	var highscore = Global.read_savegame()
	highscore_label.text = "Current record\n" + str(int(highscore))

func _on_start_pressed():
	get_tree().change_scene("res://scenes/world.tscn")

func _on_exit_pressed():
	get_tree().quit()
	

func _on_CheckBox_toggled(button_pressed):
	if button_pressed == true:
		Global.insane_mode = 2
	else:
		Global.insane_mode = 1
