# GreenThreading
Green Thread Library Implementation


Green threads are user space threads that are scheduled by a runtime library and not by the underlying operating system. Unlike pthreads, all green threads will share the same tid, but they have separate context. In this project you will start with the code provided at http://c9x.me/art/gthreads/code0.html, fork it on the github and implement the following additional features.

Ability to specify scheduling policy and set that policy at the time of the creation of the thread. You should support the FIFO and Round Robin policy with priority 1 to 99 – 1 being the lowest and 99 being the highest.
Change the gtyield function to implement the scheduling mechanism.
Write a report about green threads and what are their advantages and disadvantages. Describe your full implementation in the code as well.
