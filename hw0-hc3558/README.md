
## Homework\#0 ##

### Account Initialization ###

Please follow these steps to complete the initialization of your account on Gogs
and on the virtual machine you will be using for all assignments.
Note that your user accounts include already a pair of RSA keys to access repositories.
Feel free to change those keys if you know what you are doing.

- **Change password on Gogs**:
  Click on the top-right icon in Gogs and select [Your
  Settings](https://soc.cs.columbia.edu/user/settings). On the left menu
  select [Password](https://soc.cs.columbia.edu/user/settings/password).
- **Change password on your assigned virtual machine (VM) and clone the howework repo**
    - Connect to the VM

        From Linux or Mac use the following commands. The default password is **socp#F2024**
        ```
        local_user@hostname:$ ssh -X \<user\>@\<host\>.cs.columbia.edu
        ```
        From Windows, install an SSH client (e.g. [Putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)) and configure an SSH session.
        - In the "Session" window type \<user\>@\<host\>.cs.columbia.edu under "Host Name".
        - Select SSH as connection type.
        - Give a name to the session (e.g. \<host\>) under "Saved Sessions"
        - Select "Window"-"Selection" and set the "Action of mouse buttons" to "xterm"
        - Select "Connection"-"SSH"-"X11" and check "Enable X11 forwarding"
        - Go back to the "Session" window, save the session and open the connection

    - Change password and then clone your repository
        ```
        \<user\>@\<host\>:~$ passwd
        \<user\>@\<host\>:~$ git clone git@soc.cs.columbia.edu:socp2024/hw0-\<user\>.git
        ```

  
### Homework Assignment ###

In this assignment we use **Mojo CNN**, a C++ Convolutional Neural Network (CNN)
package available at: https://github.com/gnawice/mojo-cnn. We will use this 
package for other assignments throughout the semester. For this homework
it is not necessary that you understand all the details of the package.

In this assignment you are required to create a *Makefile* for the C++ program
whose source code is in the directories `inc`(headers) and `src`(sources). 
**Important**: the source code should not be moved from these directories.
In addition to `inc` and `src`, there are other two directories:

 - `data`: contains two images (*airplane.bmp* and *frog.bmp*) used for testing;

 - `models`: this directory contains the trained CNN model (dwarf7.mojo). 

For your convenience the current directory contains a *Makefile* template that
you can modify to complete the homework. The *Makefile* already contains the
rule for the target **data** that allows you to download the CNN model (in
the `models` directory) necessary to run the Mojo CNN application. You are
required to add rules for the following tasks:

- **all**: do the same as **dwarf**;
   
- **dwarf**: generate the executable *dwarf* in the same directory of the *Makefile*;

- **dwarf-run-airplane**: run the executable *dwarf* by using *airplane.bmp* as input;

- **dwarf-run-frog**: run the executable *dwarf* by using *frog.bmp* as input;

- **clean**: clean the working directory from all the compilation files
   including the executable file *dwarf* created with the target **dwarf**.

Make sure that **dwarf-run-airplane** and **dwarf-run-frog** can be executed only 
after the source
code has been already compiled. You need to specify the correct dependencies
to satisfy this requirement.

### How to Check Your Work:

By typing the following two commands you should obtain:

```
$ make dwarf-run-airplane
Loading DWARF7 model...
  l0: in - input 34 34 3
  l1: c1.1 - convolution 34 34 3 32 0 1
  l2: c1.2 - convolution 34 34 3 32 1 1 mpool 2x2
  l3: c2.1 - convolution 18 18 3 64 1 1 mpool 2x2
  l4: c3.1 - convolution 10 10 3 128 1 0 mpool 2x2
  l5: fc1 - fully_connected 64 1
  l6: fc2 - fully_connected 10 0

Classifying image...
Results:
  1: label|score:	"airplane" | 0.999998
  2: label|score: 	"ship" | 0.91738

$ make dwarf-run-frog
Loading DWARF7 model...
  l0: in - input 34 34 3
  l1: c1.1 - convolution 34 34 3 32 0 1
  l2: c1.2 - convolution 34 34 3 32 1 1 mpool 2x2
  l3: c2.1 - convolution 18 18 3 64 1 1 mpool 2x2
  l4: c3.1 - convolution 10 10 3 128 1 0 mpool 2x2
  l5: fc1 - fully_connected 64 1
  l6: fc2 - fully_connected 10 0

Classifying image...
Results:
  1: label|score:	"frog" | 1
  2: label|score: 	"horse" | 5.53526e-06

```

When you have completed your work, make sure to **push** your *Makefile* 
onto the Git **remote repository**. 

**Important**: Failing to do so is equivalent to failing the homework.

### Additional Notes: ###

- A basic tutorial on the GNU Make utility and on how to prepare a *Makefile* is
  available on the course [resources](https://soc.cs.columbia.edu/socp2024/fall2024/src/master/resources).
  There is much more to the make facility than what it is listed there. For more information,
  consult the [GNU documentation](http://www.gnu.org/software/make/manual/make.html).

- A basic tutorial on Git is available on the course [Wiki page](https://soc.cs.columbia.edu/socp2024/fall2024/wiki/_pages).
  This tutorial explains the basic commands that you will most often need during
  the course. Remember that to correctly update the remote repository you have
  to do a "add, commit and push" sequence of Git commands.

- **Important**: DO NOT ADD OBJECT, EXECUTABLE OR ANY AUTOMATICALLY GENERATED OUTPUT FILES TO THE GIT REPOSITORY! 
  THIS IS A STRICT RULE FOR ALL OF THE HOMEWORK ASSIGNMENTS!
