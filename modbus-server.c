#include <stdio.h>
#include <modbus.h>
#include <bits/select.h>

int main(void)
{
  modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
  int server_socket = modbus_tcp_listen(ctx, 10);
  if (server_socket > 0)
  {
    printf("Server Started\n");
  }
  modbus_mapping_t *mb_mapping = modbus_mapping_new(0, 0, 0, 0);
  uint8_t request[20];
  uint8_t response[20];
  for (;;)
  {
    printf("Ready to listen socket\n");
    int request_socket = modbus_tcp_accept(ctx, &server_socket);
    modbus_receive(ctx, &request[0]);
    for (size_t i = 0; i < 20; i++)
    {
      printf("0x%02x ", *(request + i));
    }
    modbus_reply(ctx, &response[0], 20, mb_mapping);
    printf("\n");
  }
  modbus_close(ctx);
  modbus_free(ctx);
}