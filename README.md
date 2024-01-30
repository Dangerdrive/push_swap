# push_swap

For this project I included a few other goals for me: learn some test-driven development and how to be less reliant on mouse. 

I started using IntelliJ Clion as IDE, but configured keymap to be as VSCode so going back and forth between IDEs don't bring me much trouble.

This the keybindings I kept note:

``alt + 1``: alternates between project and editor

``alt + Insert``: New... (file, directory, etc)

``ctrl + K``: commit dialog


clion . & disown


```bash
docker build -t push_swap_test_image .
```
docker build is the command to build a Docker image.
-t push_swap_test_image assigns a tag/name to your image, in this case, push_swap_test_image.

```bash
docker run -it -v $(pwd):/push_swap_test push_swap_test_image
```
docker run creates and starts a Docker container from the specified image.
-it allows you to interact with the container via the terminal.
-v $(pwd):/push_swap_test mounts your current working directory (presumably where your push_swap_test project files are) to the /push_swap_test directory in the container. This allows for two-way file synchronization: changes made in the container's /push_swap_test directory will reflect in your host machine's directory, and vice versa.
push_swap_test_image is the name of the Docker image to use, as tagged earlier.

To be able to use google test I had to set a Dockerfile
1- Creates the image in docker, it must be run only once:
docker build -t gtest .

2- Create container:
docker run -v .:/push_swap_test -it gtest

3- Execute the tests:
make runTests