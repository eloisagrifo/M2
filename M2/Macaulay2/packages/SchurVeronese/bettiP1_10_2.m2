--This file computes Betti tables for P^1 for d = 10 and b = 2
A := degreesRing 2
new HashTable from {
--tb stands for Total Betti numbers
"tb"=>new HashTable from {(7,0) => 0, (6,1) => 480, (7,1) => 225, (8,0) => 0, (8,1) => 60, (9,0) => 0, (9,1) => 7, (0,0) => 3, (0,1) => 0, (1,0) => 20, (2,0) => 45, (1,1) => 0, (3,0) => 0, (2,1) => 0, (4,0) => 0, (3,1) => 210, (5,0) => 0, (4,1) => 504, (5,1) => 630, (6,0) => 0},
--mb stands for Multigraded Betti numbers
"mb"=>new HashTable from {(7,0) => 0, (6,1) => A_0^48*A_1^24+2*A_0^47*A_1^25+4*A_0^46*A_1^26+7*A_0^45*A_1^27+10*A_0^44*A_1^28+14*A_0^43*A_1^29+19*A_0^42*A_1^30+24*A_0^41*A_1^31+29*A_0^40*A_1^32+34*A_0^39*A_1^33+37*A_0^38*A_1^34+39*A_0^37*A_1^35+40*A_0^36*A_1^36+39*A_0^35*A_1^37+37*A_0^34*A_1^38+34*A_0^33*A_1^39+29*A_0^32*A_1^40+24*A_0^31*A_1^41+19*A_0^30*A_1^42+14*A_0^29*A_1^43+10*A_0^28*A_1^44+7*A_0^27*A_1^45+4*A_0^26*A_1^46+2*A_0^25*A_1^47+A_0^24*A_1^48, (8,0) => 0, (7,1) => A_0^51*A_1^31+2*A_0^50*A_1^32+4*A_0^49*A_1^33+6*A_0^48*A_1^34+9*A_0^47*A_1^35+11*A_0^46*A_1^36+14*A_0^45*A_1^37+16*A_0^44*A_1^38+19*A_0^43*A_1^39+20*A_0^42*A_1^40+21*A_0^41*A_1^41+20*A_0^40*A_1^42+19*A_0^39*A_1^43+16*A_0^38*A_1^44+14*A_0^37*A_1^45+11*A_0^36*A_1^46+9*A_0^35*A_1^47+6*A_0^34*A_1^48+4*A_0^33*A_1^49+2*A_0^32*A_1^50+A_0^31*A_1^51, (9,0) => 0, (8,1) => A_0^53*A_1^39+2*A_0^52*A_1^40+3*A_0^51*A_1^41+4*A_0^50*A_1^42+5*A_0^49*A_1^43+6*A_0^48*A_1^44+6*A_0^47*A_1^45+6*A_0^46*A_1^46+6*A_0^45*A_1^47+6*A_0^44*A_1^48+5*A_0^43*A_1^49+4*A_0^42*A_1^50+3*A_0^41*A_1^51+2*A_0^40*A_1^52+A_0^39*A_1^53, (9,1) => A_0^54*A_1^48+A_0^53*A_1^49+A_0^52*A_1^50+A_0^51*A_1^51+A_0^50*A_1^52+A_0^49*A_1^53+A_0^48*A_1^54, (0,0) => A_0^2+A_0*A_1+A_1^2, (0,1) => 0, (1,0) => A_0^11*A_1+2*A_0^10*A_1^2+2*A_0^9*A_1^3+2*A_0^8*A_1^4+2*A_0^7*A_1^5+2*A_0^6*A_1^6+2*A_0^5*A_1^7+2*A_0^4*A_1^8+2*A_0^3*A_1^9+2*A_0^2*A_1^10+A_0*A_1^11, (2,0) => A_0^19*A_1^3+A_0^18*A_1^4+2*A_0^17*A_1^5+2*A_0^16*A_1^6+3*A_0^15*A_1^7+3*A_0^14*A_1^8+4*A_0^13*A_1^9+4*A_0^12*A_1^10+5*A_0^11*A_1^11+4*A_0^10*A_1^12+4*A_0^9*A_1^13+3*A_0^8*A_1^14+3*A_0^7*A_1^15+2*A_0^6*A_1^16+2*A_0^5*A_1^17+A_0^4*A_1^18+A_0^3*A_1^19, (1,1) => 0, (2,1) => 0, (3,0) => 0, (3,1) => A_0^33*A_1^9+A_0^32*A_1^10+2*A_0^31*A_1^11+3*A_0^30*A_1^12+5*A_0^29*A_1^13+6*A_0^28*A_1^14+9*A_0^27*A_1^15+10*A_0^26*A_1^16+13*A_0^25*A_1^17+14*A_0^24*A_1^18+16*A_0^23*A_1^19+16*A_0^22*A_1^20+18*A_0^21*A_1^21+16*A_0^20*A_1^22+16*A_0^19*A_1^23+14*A_0^18*A_1^24+13*A_0^17*A_1^25+10*A_0^16*A_1^26+9*A_0^15*A_1^27+6*A_0^14*A_1^28+5*A_0^13*A_1^29+3*A_0^12*A_1^30+2*A_0^11*A_1^31+A_0^10*A_1^32+A_0^9*A_1^33, (4,0) => 0, (4,1) => A_0^39*A_1^13+2*A_0^38*A_1^14+3*A_0^37*A_1^15+5*A_0^36*A_1^16+8*A_0^35*A_1^17+12*A_0^34*A_1^18+16*A_0^33*A_1^19+20*A_0^32*A_1^20+25*A_0^31*A_1^21+30*A_0^30*A_1^22+34*A_0^29*A_1^23+37*A_0^28*A_1^24+39*A_0^27*A_1^25+40*A_0^26*A_1^26+39*A_0^25*A_1^27+37*A_0^24*A_1^28+34*A_0^23*A_1^29+30*A_0^22*A_1^30+25*A_0^21*A_1^31+20*A_0^20*A_1^32+16*A_0^19*A_1^33+12*A_0^18*A_1^34+8*A_0^17*A_1^35+5*A_0^16*A_1^36+3*A_0^15*A_1^37+2*A_0^14*A_1^38+A_0^13*A_1^39, (5,0) => 0, (6,0) => 0, (5,1) => A_0^44*A_1^18+2*A_0^43*A_1^19+4*A_0^42*A_1^20+6*A_0^41*A_1^21+10*A_0^40*A_1^22+14*A_0^39*A_1^23+20*A_0^38*A_1^24+25*A_0^37*A_1^25+32*A_0^36*A_1^26+37*A_0^35*A_1^27+43*A_0^34*A_1^28+46*A_0^33*A_1^29+50*A_0^32*A_1^30+50*A_0^31*A_1^31+50*A_0^30*A_1^32+46*A_0^29*A_1^33+43*A_0^28*A_1^34+37*A_0^27*A_1^35+32*A_0^26*A_1^36+25*A_0^25*A_1^37+20*A_0^24*A_1^38+14*A_0^23*A_1^39+10*A_0^22*A_1^40+6*A_0^21*A_1^41+4*A_0^20*A_1^42+2*A_0^19*A_1^43+A_0^18*A_1^44},
--sb represents the betti numbers as sums of Schur functors
"sb"=>new HashTable from {(7,0) => {}, (6,1) => {({48,24},1)}, (7,1) => {({51,31},1)}, (8,0) => {}, (8,1) => {({53,39},1)}, (9,0) => {}, (9,1) => {({54,48},1)}, (0,0) => {({2,0},1)}, (0,1) => {}, (1,0) => {({11,1},1)}, (2,0) => {({19,3},1)}, (1,1) => {}, (3,0) => {}, (2,1) => {}, (4,0) => {}, (3,1) => {({33,9},1)}, (5,0) => {}, (4,1) => {({39,13},1)}, (5,1) => {({44,18},1)}, (6,0) => {}},
--dw encodes the dominant weights in each entry
"dw"=>new HashTable from {(7,0) => {}, (6,1) => {{48,24}}, (7,1) => {{51,31}}, (8,0) => {}, (8,1) => {{53,39}}, (9,0) => {}, (9,1) => {{54,48}}, (0,0) => {{2,0}}, (0,1) => {}, (1,0) => {{11,1}}, (2,0) => {{19,3}}, (1,1) => {}, (3,0) => {}, (2,1) => {}, (4,0) => {}, (3,1) => {{33,9}}, (5,0) => {}, (4,1) => {{39,13}}, (5,1) => {{44,18}}, (6,0) => {}},
--lw encodes the lex leading weight in each entry
"lw"=>new HashTable from {(7,0) => {}, (6,1) => {48,24}, (7,1) => {51,31}, (8,0) => {}, (8,1) => {53,39}, (9,0) => {}, (9,1) => {54,48}, (0,0) => {2,0}, (0,1) => {}, (1,0) => {11,1}, (2,0) => {19,3}, (1,1) => {}, (3,0) => {}, (2,1) => {}, (4,0) => {}, (3,1) => {33,9}, (5,0) => {}, (4,1) => {39,13}, (5,1) => {44,18}, (6,0) => {}},
--nr encodes the number of distinct representations in each entry
"nr"=>new HashTable from {(7,0) => 0, (6,1) => 1, (7,1) => 1, (8,0) => 0, (8,1) => 1, (9,0) => 0, (9,1) => 1, (0,0) => 1, (0,1) => 0, (1,0) => 1, (2,0) => 1, (1,1) => 0, (3,0) => 0, (2,1) => 0, (4,0) => 0, (3,1) => 1, (5,0) => 0, (4,1) => 1, (5,1) => 1, (6,0) => 0},
--nrm encodes the number of representations with multiplicity in each entry
"nrm"=>new HashTable from {(7,0) => 0, (6,1) => 1, (7,1) => 1, (8,0) => 0, (8,1) => 1, (9,0) => 0, (9,1) => 1, (0,0) => 1, (0,1) => 0, (1,0) => 1, (2,0) => 1, (1,1) => 0, (3,0) => 0, (2,1) => 0, (4,0) => 0, (3,1) => 1, (5,0) => 0, (4,1) => 1, (5,1) => 1, (6,0) => 0},
--er encodes the errors in the computed multigraded Hilbert series via our Schur method in each entry
"er"=>new HashTable from {(7,0) => 0, (6,1) => 480, (7,1) => 225, (8,0) => 0, (8,1) => 60, (9,0) => 0, (9,1) => 7, (0,0) => 3, (0,1) => 0, (1,0) => 20, (2,0) => 45, (1,1) => 0, (3,0) => 0, (2,1) => 0, (4,0) => 0, (3,1) => 210, (5,0) => 0, (4,1) => 504, (5,1) => 630, (6,0) => 0},
--bs encodes the Boij-Soederberg coefficients each entry
"bs"=>{3628800/1},
}