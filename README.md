# sl25
Traverses the Cayley graph of SL(2,5) with respect to two generators.

SL(2,5) is isomorphic to the binary icosahedral group AKA the Poincaré group and has 120 elements. The Poincaré group is a spherical space form group and acts geometrically on S^3. As a consequence, the Poincaré group is super-perfect (One would think that if a group were perfect, that would be the best, but, no: there are super-perfect groups. A perfect group has its first homology group equal to 0 and a super-perfect group has its first two homology groups equal to 0), and super-perfect groups were central to my dissertation topic at one point in time.

This program uses the (essentially) representation of the Poincaré group as SL(2,5) to traverse the Cayley graph of the Poincaré group with respect to the two generators S = [1,-1;1,0] and T = [-1,0;-1,-1] and write every element of the Poincaré group as a word in the generators.

I would like to rewrite this program using Python and a Python graph database library/module.
