Simulation of the L'aiguille de Buffon
================================
Version 1.0.0, 2021.09.07
-------------------
The Simulaotr of this version only works when  
- x, y position of the needle
- angle of the needle
- distance between two lines
- width, height of the paper
are having integer value.

And also, it define PI's value by myself, so I should take care that too.

Version 1.0.1. 2021.09.08
---------------------
The things updated:
- Now it can accept double values (x,y positoins, angle, ...etc)
- Upgrade some UIs
- Run faster using multi-threading
- Now it can write output in arbitrary file

Should be update:
- implementing without using defined PI value

Version 1.0.2. 2021.09.09
----------------------
The things updated:
- Now it can calculate expected pi value
- Precision of value of PI

but still I can't solve how to compute without defined PI value

Version 1.0.3 2021.09.11
----------------------
The things updated:

- Now It does 100 (experiments and compute PI value) each run.
- make Makefile
- make stat.c file to compute mean and standard deviation of the result of repeated trails

Usage
--------------------
- **./buffon [output file name here]**
- make buffon (to compile program)
- make clear (to clear present compiled program)
- make clear\_output (to clear output files)
