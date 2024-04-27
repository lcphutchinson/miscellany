## Fraction

This module provides a straightforward alternative to floats for storing and performing basic arithmetic operations on rational numbers. It is written as a companion to the matrix module, with the aim of improving readability and maintaining accuracy over multiple division operations where floats can become unreliable. 

Because the Fraction object is designed to work only with rational numbers, I've been able to include simple auto-reduction and sign correction in the constructor, so if your inputs are (20, -100), the fraction you will get back is -1/5.
