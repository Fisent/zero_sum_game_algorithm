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

def show_window(fields):
    win = tk.Tk()

    win.title = "dupa"
    text = 'o'

    position = 0;
    for i in fields:
        tk.Button(win, text=str(i)).grid(row=position, column=position)
        position += 1

    # tk.Button(win, text=)
    tk.mainloop()
