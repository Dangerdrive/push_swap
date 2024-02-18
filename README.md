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
you will do this once (except if you change container's configuration).

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

docker login
docker tag push_swap_test_image dangerdrive/push_swap_gtest:latest
docker push dangerdrive/push_swap_gtest:latest
docker pull dangerdrive/push_swap_gtest:latest




https://www.youtube.com/watch?v=wRvipSG4Mmk
"turk algorythim" 
we aim for just 3 positions on stack a.
so if stack a size > 4, the first step is to move the two first positions from a to b.

then for each a node you search for a target node in stack b.
you search for the smallest closest number in b stack. If not found, the target node is the max value.

cost analysis
we need to check which move is 'cheaper'.
To move a node from stack a to stack b, we would need to move the node to the top, and move its target to the top.

push cost = operations to bring a node on top + operation to bring its target node to top

so for instance, if the node we are calculating the cost is already on the top and its target is already on top on stack b, the cost will be 0.
If the cost is 0, there is no need to calculate the cost for the rest of the nodes, we can just push that node to stack b.

find target in b
    

find target in a



push cost on stack
    if first
        cost = 0;
    if last node
        cost = 1;
    if second node;
        cost = 1;


push cost (node, target)
    push cost on stack(node) + push cost on stack (target)

push to b(node)
while number of nodes in stack a is > 3
    find node's target
    check push cost
        if node's target = 0 
            push
        push cheapest
sort 3

push to a    
    
