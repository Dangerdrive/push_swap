# push_swap

For this project I included a few other goals for me: learn some test-driven development and how to be less reliant on mouse. 

I started using IntelliJ Clion as IDE, but configured keymap to be as VSCode so going back and forth between IDEs don't bring me much trouble.

This the keybindings I kept note:

``alt + 1``: alternates between project and editor

``alt + Insert``: New... (file, directory, etc)

``ctrl + K``: commit dialog

``ctrl + alt + 1``: open terminal

clion . & disown

To be able to use google test I had to set a Dockerfile
1- Creates the image in docker, it must be run only once:
docker build -t gtest .

2- Create container:
docker run -v .:/push_swap_test -it gtest

3- Execute the tests:
make runTests