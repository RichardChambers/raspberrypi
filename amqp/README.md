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
