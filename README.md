# Branch-Predictor

## Branch Predictor Architecture
Your design must consist of 2m 2-bit saturating counters indexed using m LSBs of each branch instruction. Each 2-bit saturating predictor starts in the 11 (Predict Taken with High Confidence) state and is updated as per the finite state machine discussed in Lecture 11. The value of m is specified in a config file config.txt. 

- Config File
The config file config.txt contains a single line with the value of m. A sample file for m=12 is provided. The largest value of m is 32 (for 32 bit PCs), but we will not input an m larger than 20.

- Trace File
The trace file, trace.txt, contains one branch per line. Each line has the PC for the corresponding branch (in hex format) followed by a single bit indicating Taken (1) or Not Taken (0). A sample trace file is provided.  
Output Format
The output from simulator should be a file trace.txt.out that has one line per branch. Each line has a single bit which indicates whether that branch was predicted as Taken (1) or Not Taken (0).
