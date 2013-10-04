cre489lab4
===========

GoBack3 ARQ - sockets send the alphabet to simulate ARQ

The Primary sends the packet to the Secondary and keeps it in a buffer until an ACK is 
received for this packet. The Primary displays an indication of sending the packet, 
together with its sequence number. 
o When the Primary receives an ACK from the Secondary, it adjusts the send window and 
removes the packet from its buffer. It also displays an indication of which packet was 
positively acknowledged. 
o When the Primary receives a NAK from the Secondary, it adjusts the send window and 
retransmits all the packets in the send window. It also displays an indication of which 
packets were negatively acknowledged and were retransmitted. 

