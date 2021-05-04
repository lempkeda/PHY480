DAVE LEMPKE
PHY 480
HW3

Grade: check --> check + w/extra credit

I have essentially zero experience with quantum mechanics and can not figure out how to do question 3.


I did ,however, get a very good result for question 4. 

Making my own adaptive central difference method. I was able to get extremely accurate ideal h values. This involves many
caluclations of the normal central difference algorithm, but it achieves excellent results without any input of what the 
correct solution is.

I obviously did not do this the best way that there is, but it seems to work very well for the function in question
in derivative_test.cpp.

My adaptive method here relies on the assumption that as h decreases, difference between two
tests of central_diff will only increase after the ideal h value is reached.

I have the ideal h value it finds simply being printed out. For the basic parameters, and using h = h / 1.2 for each of cycle
of my algorithm, I get an ideal log(h) of -4.972. This is almost exactly the minimum found when looking at the error
plot of just the central difference method.

Even using h = h /2.0 for each cycle, a value is found very close to the absolute ideal. 

My implementation is definitely liberal with computational resources and it may not perform well for all functions, but in
this case it works very well. 

