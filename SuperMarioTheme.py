import winsound

notes = {
    "c3":131,
    "d3":147,
    "e3":165,
    "f3":175,
    "g3":196,
    "a3":220,
    "b3":247,
    "c4":262, # Middle C
    "d4":294,
    "e4":330,
    "f4":349,
    "g4":392,
    "a4":440,
    "b4":494,
    "c5":523
}

# Note durations
full        = 500
dotted_half = 375
half        = 250

def play(note, duration):
    winsound.Beep(notes[note], duration)

def part_one():
    play("e4", half)
    play("e4", half)
    play("e4", dotted_half)
    play("c4", half)
    play("e4", half)
    play("g4", full)
    play("g3", full)

def part_two():
    play("c4", full)
    play("g3", full)
    play("e3", full)
    play("a3", half)
    play("b3", dotted_half)
    winsound.Beep(int((notes["a3"]+notes["b3"])/2), half) # produces a# note
    play("a3", dotted_half)
    play("g3", half)

def part_three():
    play("e4", half)
    play("g4", half)
    play("a4", dotted_half)
    play("f4", half)
    play("g4", half)
    play("e4", half)
    play("c4", dotted_half)
    play("d4", half)
    play("b3", full)

#4 - G F# F D# E
def part_four():
    play("g4", half)
    winsound.Beep(int((notes["f4"]+notes["g4"])/2), half)
    play("f4", half)
    winsound.Beep(int((notes["d4"]+notes["e4"])/2), half)
    play("e4", full)

#5 - A A C A C D
def part_five():
    play("a3", half)
    play("a3", half)
    play("c4", dotted_half)
    play("a3", half)
    play("c4", half)
    play("d4", dotted_half)


def main_song():
    part_one()
    for i in range(2):
        part_two()
        part_three()
    part_four()
    part_five()
    part_four()
    for i in range(2):
        play("c5", half)
    play("c5", full)
    part_four()
    part_five()
    winsound.Beep(int((notes["d4"]+notes["e4"])/2), full)
    play("d4", full)
    play("c4", full)

main_song()

# part_one()
# part_two()
# part_three()
# part_four()
# part_five()