Ambient noise
------------------
As we already know ambient noise is nothing but background noise what i've done in this i just found the maximum among the first 1500 samples now this is enough for us to be sure when the ambient noise ends and actual speaking starts.

YES/NO detection
 -----------------------
Out of all the values of zcr and energy we calculate we just try looking at the average of last 40% of the values of zcr and that gives us a pretty good idea of what that word might be if it's at the end less then 40 its a fricative this is bcz yes ends with a fricative that basically means that it has a low zcr while as no has high zcr due it ending with a vowel.
I've personally taken to be 20 it's more then enough for me .


Instructions to execute the code
----------------------------------------

1. The variables i've already declared them no need to change that.
2. The names of the speech input and output files should be decided
     first and written for the respective variables in the main function which i've 
      commented and there you'll be able to see where you have to type in
       the file name along with extension .
3. Since i wasn't getting dc shift i haven't taken that into considration
4.  f7 can be pressed for building the project and f5 should be
pressed for execution.
5. Output can be observed in the console window