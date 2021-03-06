import tkinter as tk

board = '''
W - white pawn
B - black pawn
o - empty field

B-----o-----B
|     |     |
| o---W---o |
| |   |   | |
| | B-B-W | |
| | |   | | |
W-B o   W-W-B
| | |   | | |
| | W-B-B | |
| |   |   | |
| o---W---o |
|     |     |
W-----B-----W
'''

WIN = None

# 0, 1, or 2
CURRENT_PHASE = 0

FIELDS_POSITIONS = [
    (0, 0), (0, 6), (0, 12),
    (2, 2), (2, 6), (2, 10),
    (4, 4), (4, 6), (4, 8),
    (6, 0), (6, 2), (6, 4), (6, 8), (6, 10), (6, 12),
    (8, 4), (8, 6), (8, 8),
    (10, 2), (10, 6), (10, 10),
    (12, 0), (12, 6), (12, 12)
]

pressed_field = -1
pressed_field_2 = -1
time_to_take = False

def first_phase_callback(number):
    print('first_phase_callback')
    global pressed_field
    pressed_field = number
    WIN.destroy()
    print('first_phase_callback ' + str(number))

def second_third_phase_callback(number):
    global pressed_field
    global pressed_field_2
    print('second_third_phase_callback ' + str(number))

    if pressed_field is -1:
        pressed_field = number
    else:
        pressed_field_2 = number
        WIN.destroy()

def take_callback(number):
    global pressed_field
    print('take_callback')

    pressed_field = number

def callback(number):
    global CURRENT_PHASE
    print('Callback, phase: ' + str(CURRENT_PHASE))
    if CURRENT_PHASE == 0:
        first_phase_callback(number)
    elif CURRENT_PHASE == 1 or CURRENT_PHASE == 2:
        second_third_phase_callback(number)
    else:
        print('CRITICAL ERROR, PHASE NOT 0, 1 or 2, phase: ' + str(CURRENT_PHASE))

def create_button(field, position, win, callback, number):
    text = ''
    color = ''
    
    if int(field) == 0:
        text = 'o'
        color = 'grey'
    elif int(field) == 1:
        text = 'W'
        color = 'white'
    elif int(field) == 2:
        text = "B"
        color = 'black'
    else:
        text = "ERRRRRROOOOR"
        color = 'red'
    return tk.Button(win, text=text, bg=color, command=lambda: callback(number)).grid(row=position[0], column=position[1], padx=15, pady=15)
    

def show_window(fields, phase, time_to_take_arg):
    print('Phase ' + str(phase))
    buttons = []

    global pressed_field
    global pressed_field_2
    global time_to_take
    pressed_field = -1
    pressed_field_2 = -1
    time_to_take = time_to_take_arg == 'yes'

    global WIN
    WIN = tk.Tk()

    WIN.title = "Nine men's morris"

    global CURRENT_PHASE
    CURRENT_PHASE = int(phase)

    for i in range(24):
        buttons.append(create_button(fields[i], FIELDS_POSITIONS[i], WIN, callback, i))

    tk.mainloop()

    out = str(pressed_field)
    if pressed_field_2 is not -1:
        out += ',' + str(pressed_field_2)

    print(out)
    return out
