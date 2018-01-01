## Using AMQP as a messaging protocol

In addition to CoAP and MQTT another major messaging protocol is AMQP which is supported
by RabbitMQ messaging broker.

It appears that a good staring point is the package `librabbitmq-dev` per this article
on Debian https://packages.debian.org/jessie/librabbitmq-dev

See https://github.com/alanxz/rabbitmq-c with sample programs and documentation for librabbitmq. See as well
this discussion thread, http://rabbitmq.1065348.n5.nabble.com/C-client-options-td28641.html 

The easiest test environment seems to be to install RabbitMQ on a Linux machine to act as
a server. See this list of RabbitMQ interview questions http://www.ezdev.org/view/rabbitmq/7176

See RabbitMQ install on Debian here http://www.rabbitmq.com/install-debian.html

See the RabbitMQ Tutorials and Quick Start Guide at http://www.rabbitmq.com/getstarted.html

The RabbitMQ default port is 5672.

## RabbitMQ setup and configuration

After installing `librabbitmq-server` you will need to set up a RabbitMQ user using the `rabbitmqctl` utility.
See [rabbitmqctl](https://www.rabbitmq.com/rabbitmqctl.8.html) which has a list of the commands and the
command syntax. The specific command to create a user is `sudo rabbitmqctl add_user user password`.

Logs for RabbitMQ are by default in /var/log/rabbitmq and these logs can be helpful in troubleshooting
problems and errors.

### Error: Logging in: a socket error occurred

An error with logging is probably one of two problems: the user and password being used in the function call
of `amqp_login()` has not been created with the `rabbitmqctl` utility or the user permissions have not been
set with the `rabbitmqctl` utility.

The command to create a user is `sudo rabbitmqctl add_user user password`.

For an error of "access to vhost '/' refused for user 'guest'" see https://stackoverflow.com/questions/17054533/allowing-rabbitmq-server-connections

The command to set user permissions is `rabbitmqctl set_permissions -p / user ".*" ".*" ".*"`
