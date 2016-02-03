General Comments:

The coverage shows that I'm covering the game initializer. While this is true, 
I'm never actually making sure it returns what is expected. As such, code coverage 
is high for this area even though I'm not actually covering it. This also applies 
to some of the draw card related functions, that are used by the initializer. I can 
see how this could be misleading in the real world, as development teams just shoot 
to get 100% code coverage, but don't do it in a useful fashion.