##
## TODO: Have singly_linked_node, linkedqueue, and linkedstack
##       each as separate libraries -- linked to stackqueue-c executable.
##
add_executable("stackqueue-c"
    "main.c"
    "singly_linked_node.h"
    "singly_linked_node.c"
    "linkedqueue.h"
    "linkedqueue.c"
    "linkedstack.h"
    "linkedstack.c"
)
