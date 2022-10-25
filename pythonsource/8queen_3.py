import kivy.app
import kivy.uix.gridlayout
import kivy.uix.boxlayout
import kivy.uix.button
import kivy.uix.textinput
import kivy.uix.label
import numpy
from kivy.config import Config

class BuzzleApp(kivy.app.App):

    def build(self):
        boxLayout = kivy.uix.boxlayout.BoxLayout(orientation="vertical")

        gridLayout = kivy.uix.gridlayout.GridLayout(rows=8, size_hint_y=9)
        boxLayout_buttons = kivy.uix.boxlayout.BoxLayout(orientation="horizontal")

        boxLayout.add_widget(gridLayout)
        boxLayout.add_widget(boxLayout_buttons)

        # Preparing the 8x8 board.
        self.all_widgets = numpy.zeros(shape=(8,8), dtype="O")

        for row_idx in range(self.all_widgets.shape[0]):
            for col_idx in range(self.all_widgets.shape[1]):
                self.all_widgets[row_idx, col_idx] = kivy.uix.button.Button(text=str(row_idx)+", "+str(col_idx), font_size=25)
                self.all_widgets[row_idx, col_idx].markup = True
                gridLayout.add_widget(self.all_widgets[row_idx, col_idx])

        # Preparing buttons inside the child BoxLayout.
        initial_button = kivy.uix.button.Button(text="Initial Population", font_size=15, size_hint_x=2)

        ga_solution_button = kivy.uix.button.Button(text="Show Best Solution", font_size=15, size_hint_x=2)

        start_ga_button = kivy.uix.button.Button(text="Start GA", font_size=15, size_hint_x=2)

        self.num_solutions_TextInput = kivy.uix.textinput.TextInput(text="8", font_size=20, size_hint_x=1)
        self.num_generations_TextInput = kivy.uix.textinput.TextInput(text="10000", font_size=20, size_hint_x=1)
        self.num_mutations_TextInput = kivy.uix.textinput.TextInput(text="5", font_size=20, size_hint_x=1)

        self.num_attacks_Label = kivy.uix.label.Label(text="# Attacks/Best Solution", font_size=15, size_hint_x=2)

        boxLayout_buttons.add_widget(initial_button)
        boxLayout_buttons.add_widget(ga_solution_button)
        boxLayout_buttons.add_widget(start_ga_button)
        boxLayout_buttons.add_widget(self.num_solutions_TextInput)
        boxLayout_buttons.add_widget(self.num_generations_TextInput)
        boxLayout_buttons.add_widget(self.num_mutations_TextInput)
        boxLayout_buttons.add_widget(self.num_attacks_Label)

        return boxLayout

Config.set('graphics', 'width', '1000')
Config.set('graphics', 'height', '600')

buzzleApp = BuzzleApp()
buzzleApp.run()
