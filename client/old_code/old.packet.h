#ifndef             PACKET_H
#define             PACKET_H

#include "file_util.h"

#include <array>

namespace packet_system{
  class packet{
    public:
      /**
       * An uninitalized packet meant to be populated later
       **/
      packet();

      /**
       * This constructor creates an acknowledgement packet.
       **/
      packet(char acknowleged);

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
      packet(file_util::file_obj& file, bool acknowledgment, 
      int order_num);


      //A filename packet
      packet(std::string filename);

      void construct_packet(char* packet);

      void assemble_sent_packet(char* packet);

      /**
       * Changes the state of the acknowledgment flag
       *
       * Param: acknowledgment the state this packet
       * is being set to.
       **/
      void set_acknowledgment(bool acknowledgment){ this->acknowledgment
       = acknowledgment; };

      /**
       * Get th value of the acknowledgment packet.
       *
       * Returns: The value of this acknowledgment.
       **/
      bool get_acknowledgment() const { return acknowledgment; };

      short get_data_size() const { return data_size; };

      char* get_data() { return data; }

      bool is_file() const { return file_req; };

      bool is_partial() { return data_size < MAX_DATA_SIZE; }

      /**
       * Destroys the packet. Specifically the 
       * packet_contents. 
       **/
      ~packet();

      //1024 + 2header + 2null33 + 1footer.
      static constexpr short PACKET_SIZE = 1029;

    private:
      //The contents of the packet, Not including header stuff or the checksum
      char* data;

      //The size of the packet. Normally this matters in the case of a 
      //partial packet. Otherwise its just a default packet size. 
      unsigned short data_size;
      int order_num;
      char code;
      char footer;

      //Indicates weather this packet has been acknowledged.
      //Applies to normal packets only.
      bool acknowledgment;

      bool file_req{false};


      static constexpr short MAX_DATA_SIZE = 1024;
      static constexpr char PACKET_CODE_SIZE = 1;
      static constexpr char ORDER_NUM_SIZE = 1;
      static constexpr char ORDER_CHAR_OFFSET = 48;
      static constexpr char HEADER_OFFSET = 2;
  };
}

#endif
