-------------------------------------------------------------------
```
These are the arithmetic average for the C implementation:

SNU_512_5x5_float 0.047165222
SNU_512_5x5_int 0.033267556
cat_512_7x7_float 0.085038111
cat_512_7x7_int 0.051196667
301_512_3x3_float 0.020888444
301_512_3x3_int 0.020622

301_512_SNU_512_overlay_0.1_float 0.003763571
301_512_SNU_512_overlay_0.1_int 0.001886667
301_512_SNU_512_overlay_0.5_float 0.003720111
301_512_SNU_512_overlay_0.5_int 0.001774667
301_512_SNU_512_overlay_0.8_float 0.00369
301_512_SNU_512_overlay_0.8_int 0.001877778

301_512_SNU_512_merge_0.5_float 0.002744875
301_512_SNU_512_merge_0.5_int 0.002556286
```
-------------------------------------------------------------------
```
These are the arithmetic average for the Python implementation:

SNU_512_5x5_float 12.729409
SNU_512_5x5_int 12.1913404
cat_512_7x7_float 23.60773567
cat_512_7x7_int 22.41546533
301_512_3x3_float 5.9234148
301_512_3x3_int 5.4311374

301_512_SNU_512_overlay_0.1_float 0.9762972
301_512_SNU_512_overlay_0.1_int 0.8613498
301_512_SNU_512_overlay_0.5_float 0.8441048
301_512_SNU_512_overlay_0.5_int 0.950991833
301_512_SNU_512_overlay_0.8_float 1.0110094
301_512_SNU_512_overlay_0.8_int 0.940899167

301_512_SNU_512_merge_0.5_float 0.940278667
301_512_SNU_512_merge_0.5_int 1.071113429
```
-------------------------------------------------------------------
```
Method to find the percentage improvement in speed:

Percentage improvement = ((Old time - New time)/ Old time) * 100

For example:
Old time= SNU_512_5x5_float =0.047165222
New time= SNU_512_5x5_int =0.033267556

Percentage improvement = ((0.047165222-0.033267556)/0.047165222)*100
                       = 29.47%
approximately 29.47% improvement in speed when using the integer method.
```
-------------------------------------------------------------------
### C implementation

In the C implementation, using the int mode definitely seems to decrease the amount of time required to create separate images both ways in blur and in blend.

In the blur method, using the int method decreased the time from the float method. The improvement in time differed for each kernel size. For the 3x3, It was improved by about 1%. In the 5x5 kernel it improved about 30%. In the 7x7 kernel it improved by 40%.

In the blend method (overlay), using the int method improved the time from the float method by around 50%. For (merge) it improved the time by around 6.8%.

-------------------------------------------------------------------
### Python implementation

However in the python implementation, there seems to be no stark contrast between the time required to create the images. 

In the blur method, using the integer method did improved the time it took to create the image than the float method by 8.3%, 4.2%, and 5% corresponding to the kernel size 3x3, 5x5, and 7x7.

In the blend method, in some improved the time by 11.7%, 7%, while some deproved the time by 12.6% and 13.9%. Thus there was not enough evidence that using the int type improved the speed for creating the images.

-------------------------------------------------------------------
### Conclusion

In conclusion, we were able to see the differences in performance between the C programming language and Python. The C implementation seems to benefit more from using fixed-point arithmetic compared to the Python implementation, resulting in more significant performance improvements. However it is important to note that the performance can vary due to hardware and other factors. 

