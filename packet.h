#ifndef             PACKET_H
#define             PACKET_H

#include <array>

namespace server{
  namespace packet_system{
    class packet{
      public:
        /**
         * This constructor creates an acknowledgement packet.
         * It consist of a four chars that represent 'a' 'c' 'k' and 
         * number of the packet acknowleged
         *
         * Param: ack_packet the number of the packet being acknowledged 
         **/
        packet(unsigned char ack_packet);

        /**
         * This counstructor creates a regular packet that is used to 
         * send data. It creates both partial and full packets
         * It manipulates the filestream to get the data instead of 
         * having that in a separate class. Since this class is also
         * used by the client, it also allows the acknowledgment flag
         * to be set as needed.
         *
         * Param: file_stream The file stream of the file being sent
         * over the server.
         * Param: acknowledgment, sets the flag for this packet.
         **/
        packet(&std::ifstream file_stream, bool acknowledgment);

        /**
         * Changes the state of the acknowledgment flag
         *
         * Param: acknowledgment the state this packet
         * is being set to.
         **/
        void set_acknowledgment(bool acknowledgment);

        /**
         * Get th value of the acknowledgment packet.
         *
         * Returns: The value of this acknowledgment.
         **/
        bool get_acknowledgment() const;

        /**
         * Destroys the packet. Specifically the 
         * packet_contents. 
         **/
        ~packet();

      private:
        //The actual contents that will be sent. this includes the data, a packet type code, an order number,
        //and in the case of a partial packet, its size.
        unsigned char* packet_contents;

        //The checksum for this packet
        unsigned short checksum;

        //The size of the packet. Normally this matters in the case of a partial packet. Otherwise its just a 
        //default packet size. 
        unsigned short packet_size;

        //The order number for this packet in the sliding window. 
        unsigned char window_order_num;

        //A stl array to hold the packet code to indicate what type of packet this packet is.
        //I use a stl array because I generally think its safer to use and if I have to pass it around later then I won't 
        //have an issue with passing it.
        std::array<char, 3> packet_code;

        //Indicates weather this packet has been acknowledged.
        //Applies to normal packets only.
        bool acknowledgment;

        //A private member function to calculate the checksum
        void calculate_checksum();

    };
  }
}

#endif
