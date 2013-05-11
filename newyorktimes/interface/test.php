<?php
// outputs the username that owns the running php/httpd process
// (on a system with the "whoami" executable in the path)
exec('demo/searching happy newyork',$output);
var_dump($output);
?>