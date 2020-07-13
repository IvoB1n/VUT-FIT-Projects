#!/usr/bin/env python3

import unittest
from mathlib import MathLib
class matlibTest(unittest.TestCase):

    def setUp(self):
        self.matlib = MathLib()

    def test_add(self):
        self.assertEqual(self.matlib.add(1, 2), 3)
        self.assertEqual(self.matlib.add(-2, 2), 0)
        self.assertEqual(self.matlib.add(0.002, -0), 0.002)
        self.assertEqual(self.matlib.add(-2.5, -1.5), -4)
        self.assertEqual(self.matlib.add(0, 0), 0)
        self.assertRaises(TypeError, self.matlib.add)
        self.assertRaises(TypeError, self.matlib.add, 2)
              
    def test_sub(self):
        self.assertEqual(self.matlib.sub(4, 2), 2)
        self.assertEqual(self.matlib.sub(0, 2), -2)
        self.assertEqual(self.matlib.sub(-0.00005, 4), -4.00005)
        self.assertEqual(self.matlib.sub(4, -2), 6)
        self.assertEqual(self.matlib.sub(0, 0), 0)
        self.assertRaises(TypeError, self.matlib.sub)
        self.assertRaises(TypeError, self.matlib.sub, 2)
        
    def test_mul(self):
        self.assertEqual(self.matlib.mul(2, 5), 10)
        self.assertEqual(self.matlib.mul(0.0005, 0.1), 0.00005)
        self.assertEqual(self.matlib.mul(-2, 5), -10)
        self.assertEqual(self.matlib.mul(-2, -5), 10)
        self.assertEqual(self.matlib.mul(2, 0), 0)
        self.assertEqual(self.matlib.mul(0, 0), 0)
        self.assertRaises(TypeError, self.matlib.mul)
        self.assertRaises(TypeError, self.matlib.mul, 2)
          
    def test_div(self):
        self.assertEqual(self.matlib.div(8, 4), 2)
        self.assertEqual(self.matlib.div(8, -2), -4)
        self.assertEqual(self.matlib.div(8, 0.4), 20)
        self.assertEqual(self.matlib.div(0.8, 4), 0.2)
        self.assertEqual(self.matlib.div(0, 4), 0)
        self.assertEqual(self.matlib.div(-0, 4), 0)
        self.assertRaises(ZeroDivisionError, self.matlib.div, 5, 0)
        self.assertRaises(TypeError, self.matlib.div)
        self.assertRaises(TypeError, self.matlib.div, 2)

    def test_fac(self):
         self.assertEqual(self.matlib.fac(5), 120)
         self.assertEqual(self.matlib.fac(1), 1)
         self.assertEqual(self.matlib.fac(0), 1)
         self.assertEqual(self.matlib.fac(2), 2)
         self.assertRaises(TypeError, self.matlib.fac)
         self.assertRaises(Exception, self.matlib.fac, -2)
         self.assertRaises(Exception, self.matlib.fac, 1.55)

    def test_root_n(self):
        self.assertEqual(self.matlib.root_n(4, 2), 2)
        self.assertEqual(self.matlib.root_n(0, 5), 0)
        self.assertEqual(self.matlib.root_n(1, 6), 1)
        self.assertEqual(self.matlib.root_n(10.89, 2), 3.3)
        self.assertEqual(self.matlib.root_n(10.903204, 2), 3.302)
        self.assertRaises(TypeError, self.matlib.root_n)
        self.assertRaises(Exception, self.matlib.root_n, -2)

    def test_pow_x_y(self):
        self.assertEqual(self.matlib.pow_x_y(4, 2), 16)
        self.assertEqual(self.matlib.pow_x_y(0.5, 3), 0.125)
        self.assertEqual(self.matlib.pow_x_y(1, 200), 1)
        self.assertEqual(self.matlib.pow_x_y(0, 200), 0)
        self.assertEqual(self.matlib.pow_x_y(0, 0), 1)
        self.assertEqual(self.matlib.pow_x_y(251, 0), 1)
        self.assertEqual(self.matlib.pow_x_y(251, 0), 1)
        self.assertEqual(self.matlib.pow_x_y(2, -2), 0.25)
        self.assertEqual(self.matlib.pow_x_y(2, 2.2), 4.59479341998814)
        self.assertRaises(TypeError, self.matlib.pow_x_y)

    def test_log_n(self):
        self.assertEqual(self.matlib.log_n(2), 0.6931471805599454)
        self.assertEqual(self.matlib.log_n(1.1), 0.09531017980432499)
        self.assertEqual(self.matlib.log_n(1), 0)
        self.assertEqual(self.matlib.log_n(2.8), 1.0296194171811583)
        self.assertEqual(self.matlib.log_n(284), 5.648974238161206)
        self.assertRaises(Exception, self.matlib.log_n, 0)
        self.assertRaises(Exception, self.matlib.log_n, 0)
        self.assertRaises(Exception, self.matlib.log_n, -1) 
        self.assertRaises(TypeError, self.matlib.log_n)


    
        
if __name__ == '__main__':
    unittest.main()