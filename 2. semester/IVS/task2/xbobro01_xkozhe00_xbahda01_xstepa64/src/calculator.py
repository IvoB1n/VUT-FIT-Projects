from PyQt5 import QtWidgets, QtCore
from gui.calculator_gui import Ui_MainWindow
from mathlib import MathLib as ml
import webbrowser

class CalculatorWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.flag_op = 0
        self.flag_clear = 0
        self.setupUi(self)
        self.show()

        self.button_0.clicked.connect(self.button_pressed)
        self.button_1.clicked.connect(self.button_pressed)
        self.button_2.clicked.connect(self.button_pressed)
        self.button_3.clicked.connect(self.button_pressed)
        self.button_4.clicked.connect(self.button_pressed)
        self.button_5.clicked.connect(self.button_pressed)
        self.button_6.clicked.connect(self.button_pressed)
        self.button_7.clicked.connect(self.button_pressed)
        self.button_8.clicked.connect(self.button_pressed)
        self.button_9.clicked.connect(self.button_pressed)

        self.button_div.clicked.connect(self.op_button_pressed)
        self.button_mult.clicked.connect(self.op_button_pressed)
        self.button_minus.clicked.connect(self.minus_button_pressed)
        self.button_plus.clicked.connect(self.op_button_pressed)
        self.button_fac.clicked.connect(self.op_button_pressed)
        
        # self.button_lbracket.clicked.connect(self.button_pressed)
        # self.button_rbracket.clicked.connect(self.button_pressed)
        self.button_lg.clicked.connect(self.op_button_pressed)
        self.button_pow_x_y.clicked.connect(self.op_button_pressed)
        self.button_root2.clicked.connect(self.op_button_pressed)
        self.button_comma.clicked.connect(self.button_pressed)

        self.button_eq.clicked.connect(self.eq_button_pressed)

        self.button_clear.clicked.connect(self.clear_button_pressed)
        self.button_del.clicked.connect(self.del_button_pressed)

        self.button_help.clicked.connect(self.help_button_pressed)

        self.label.setText("")

    def button_pressed(self):
        if self.flag_clear == 1:
            self.label.setText("")
            self.flag_clear = 0

        button = self.sender()

        self.label.setText(self.label.text() + button.text())

    def op_button_pressed(self):
        self.flag_clear = 0
        if self.flag_op == 0:
            button = self.sender()

            self.label.setText(self.label.text() + button.text())
            self.flag_op = 1

            return self.flag_op

    def minus_button_pressed(self):
        self.flag_clear = 0
        button = self.sender()

        self.label.setText(self.label.text() + button.text())

    def clear_button_pressed(self):
        self.label.setText("")

    def del_button_pressed(self):
        new_text = self.label.text()
        if new_text != "":
            if new_text[-1] == "n":
                new_text = new_text[:-2]
            elif new_text[-1] == "r" or new_text[-1] == "x":
                new_text = ""
            else:
                new_text = new_text[:-1]
        self.label.setText(new_text)

    def eq_button_pressed(self):
        self.flag_op = 0
        self.flag_clear = 1
        equation = str(self.label.text())
        try:
            result = str(ml.solve_eq(equation))
        except:
            result = "Incorrect Syntax"

        self.label.setText(result)

    def help_button_pressed(self):
        webbrowser.open_new(r'../dokumentace.pdf')