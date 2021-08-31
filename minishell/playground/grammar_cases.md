## ``<`` operator  

**syntax**: ``[left] < [right]``  

**if just ``<`` with no ``left`` or ``right``** it fails;  
**if ``left`` doesn't exist, ``right`` must exist** ``right`` content is printed (with ``less``?);  
**if ``left`` and ``right`` exist:**   
	- ``left`` can be a command;   
	- if ``left`` is a file with a command inside (eg. ``wc``), outputs ``zsh: redirection with no command``?  
	- if ``left`` is not a command, ``zsh: command not found: file``.  

## the ``(`` and ``)``

**if ``(command)``**, it works;  
**if ``((command))``**, it doesn't work;  
	- any subsequent number of paren will fail, if balanced, and attribute the error to the middle command;  
	- if unbalanced, the error is on the unbalanced paren;  


