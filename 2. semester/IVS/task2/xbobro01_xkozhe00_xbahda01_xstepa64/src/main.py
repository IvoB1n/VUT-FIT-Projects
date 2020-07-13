import sys
from PyQt5.QtWidgets import QApplication
from calculator import CalculatorWindow

App = QApplication(sys.argv)

Calculator = CalculatorWindow()

sys.exit(App.exec_())
