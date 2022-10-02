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
  modbus_mapping_t *mb_mapping = modbus_mapping_new(1, 1, 1, 1);
  uint8_t request[MODBUS_RTU_MAX_ADU_LENGTH];
  for (;;)
  {
    printf("Ready to listen socket\n");
    int request_socket = modbus_tcp_accept(ctx, &server_socket);
    int len = modbus_receive(ctx, &request[0]);
    for (size_t i = 0; i < 20; i++)
    {
      printf("[%ld]:0x%02x\n", i, *(request + i));
    }
    modbus_reply(ctx, &request[0], len, mb_mapping);
    printf("\n");
  }
  modbus_close(ctx);
  modbus_free(ctx);
}