#!/usr/bin/env python3
""" @package MathLibrary
    Module for basic mathematical operations and functions.

This module contains the class MathLib that describes basic mathematical operations and functions.
This module describes the functions of addition, subtraction, multiplication, division, factorial, root, and natural logarithm.
"""

class MathLib():
    """ Class for basic mathematical operations and functions.

    This class contains the functions that describes basic mathematical operations and functions.
    This class describes functions such as:
        add(a, b) - addition of two numbers
        sub(a, b) - subtraction of two numbers
        mul(a, b) - multiplication of two numbers
        div(a, b) - division of two numbers
        mod(a) - calculating the number module
        fac(a) - calculating the factorial of a number
        root_n(a, b) - calculating the root of a number
        pow_x_y(a, b) - calculating the power of a number
        log_n(a) - calculating the logarithm of a number
    """
    # a + b
    @staticmethod
    def add(a, b):
        """ Function for calculating the sum of two numbers.

        This function has two arguments. Arguments can be integer or fractional numbers.
        The second argument is added to the first argument.
        The function returns the sum of two arguments.
        """
        return a + b
    
    # a - b
    @staticmethod
    def sub(a, b):
        """ Function for calculating the difference between two numbers.

        This function has two arguments. Arguments can be integer or fractional numbers.
        The second argument is subtracted from the first argument.
        The function returns the difference between two numbers.
        """  
        return a - b
    
    # a * b
    @staticmethod
    def mul(a, b):
        """ Function for calculating the product of two arguments.

        This function has two arguments. Arguments can be integer or fractional numbers.
        The first argument is multiplied by the second.
        The function returns the product of two arguments.
        """
        return round(a * b, 14)

    # a / b
    @staticmethod
    def div(a, b):
        """ The function calculates relation of two arguments.

        This function has two arguments. Arguments can be integer or fractional numbers.
        The first argument is divided into the second.
        The function returns the result of dividing the first argument by the second.
        """
        return round(a / b, 14)
    
    # mod(a)
    @staticmethod
    def mod(a):
        """ The function calculates the module of a number.

        The function has one argument. Argument can be integer or fractional number.
        The function checks the sign of a number.
        If the number is non-negative, the function returns this number.
        If the number is negative, the function returns a number with the opposite sign.
        """
        if(a < 0):
            return a * -1
        else:
            return a

    # factorial(a)
    @staticmethod
    def fac(a):
        """ The function calculates the factorial of a number.

        The function has one argument. Argument can be integer.
        If the argument is not an integer, the function returns an error.
        The function also returns an error if the number is negative.
        If successful, the function calculates the factorial and returns it.
        """
        if (int(a) != a or a < 0):
            # if argument is float or negative, return exception
            raise Exception ('Wrong argument!')
        a = int(a)
        fact = 1
        # counting factorial
        for i in range (1, a+1):
            fact = fact * i
        return fact

    # sqrt^b(a) - interval method
    @staticmethod
    def root_n(a, b):
        """ The function calculates the root of a number.

        This function has two arguments. 
        Arguments can be integer or fractional numbers. The second argument can't be zero.
        If the first argument will be neagtive, second argument must be odd.
        If the first argument will be neagtive and second argument will be even, function returns error.
        The first argument is a number from which the root is extracte. The second argument is an indicator of the root.
 
        If successful, the function calculates the root and returns it.
        """
        if ((b%2 == 0) and a < 0):
            # if argument b is even and argument a is negative, return exception
            raise Exception ('Wrong argument!')
        return round(a**(1/b), 14)
    
    # if b > 0 and b != int, a ^ b - interval method
    @staticmethod
    def pow_x_y(a, b):
        """ The function calculates the power of a number.

        This function has two arguments. Arguments in this function might be floats.
        The first argument is a number that will be raised to a power. The second argument is an indicator of the power.
        The function returns a number raised to a power.
        """
        return round(a**b, 14)

    # ln(a) - interval method
    @staticmethod
    def log_n(a):
        """ The function calculates the logarithm of a number.

        This function has one argument. Argument in this function has float type and must be positive and greater than zero.
        If the argument is not positive or null, the function returns an error.
        The function calculates the logarithm of a number using the interval method.
        The logarithm is calculated from the exponent.
        If successful, the function calculates the logarithm and returns it.
        """
        # value of exponent
        e = 2.718281828459045
        min = 0
        # conditions for max min (interval method)
        if (a >= e):
            max = a
        elif (e > a >= 1):
            max = 1
        elif (a > 0):
            min = -999
            max = 0
        else:
            # if argument a is negative, return exception
            raise Exception ('Wrong argument!')
        # variable for repeating cycle
        # (if cycle will repeat more than once old will be same as central and cycle will be over)
        old = -9999
        central = 0
        result = e ** central
        
        while (a > 0) and (result != a):
            # interval method
            central = (max + min) / 2
            
            # result = e^central
            result = e ** central
            if (result > a):
                max = central
            elif (result < a):
                min = central
            if (central == old):
                break
            old = central
        return central
        
    @staticmethod
    def a_sum(num_list):
        """ The function calculates arithmetic sum .

        This function has one argument. 
        First argument is list of numbers.
 
        If successful, the function calculates the arithmetic sum of numbers in list(first argument).
        """
        s = 0
        for el in num_list:
            s += el
        
        return s

    @staticmethod
    def parse_eq(equation):
        """ The function parse an equation stored in string.

        The function has one argument. Argument should be string that contains math equation.
        The function parse an equation.
        
        If successful, the function returns two lists ([numbers][operatores]).
        """
        operators = ['+', '-', '*', '/', "!", "n", "^", "√"]
        op_out = []
        num_out = []
        buff = []
        for c in equation:
            if c in operators:
                num_out.append(''.join(buff))
                buff = []
                op_out.append(c)
            else:
                buff.append(c)
        num_out.append(''.join(buff))

        num_length = len(num_out)
        if len(op_out) != 1:
            for i in range(num_length):
                if num_out[i] == '':
                    num_out[i + 1] = op_out[i] + num_out[i + 1]
                    op_out.remove(op_out[i])

        for element in num_out:
            if element == 'L'or element == '':
                num_out.remove(element)

        return num_out, op_out

    @staticmethod
    def solve_eq(equation):
        """ The function calculates parsed equation.

        The function has one argument. Argument should be string that contains math equation.
        The function calls parse_eq function and calculate returned value.
        
        If successful, the function returns one number - equation result.
        """
        parsed_eq = MathLib.parse_eq(equation)
        i = 0

        if len(parsed_eq[i]) == 0 or len(parsed_eq[i + 1]) == 0:
            return("Syntax error")

        for j in range(len(parsed_eq[i])):
            parsed_eq[i][j] = float(parsed_eq[i][j])

        if parsed_eq[i + 1][i] == '+':
            solved_eq = MathLib.add(parsed_eq[i][i], parsed_eq[i][i + 1])
        elif parsed_eq[i + 1][i] == '-':
            solved_eq = MathLib.sub(parsed_eq[i][i], parsed_eq[i][i + 1])
        elif parsed_eq[i + 1][i] == '*':
            solved_eq = MathLib.mul(parsed_eq[i][i], parsed_eq[i][i + 1])
        elif parsed_eq[i + 1][i] == '/':
            solved_eq = MathLib.div(parsed_eq[i][i], parsed_eq[i][i + 1])
        elif parsed_eq[i + 1][i] == '!':
            solved_eq = MathLib.fac(parsed_eq[i][i])
        elif parsed_eq[i + 1][i] == '^':
            solved_eq = MathLib.pow_x_y(parsed_eq[i][i], parsed_eq[i][i + 1])
        elif parsed_eq[i + 1][i] == '√':
            solved_eq = MathLib.root_n(parsed_eq[i][i], 2)
        else:
            solved_eq = MathLib.log_n(parsed_eq[i][i])

        if int(solved_eq) == solved_eq:
            return str(int(solved_eq))
        else:
            return str(round(solved_eq, 7))