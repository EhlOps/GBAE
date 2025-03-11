#include <cart.h>

typedef struct {
    char filename[1024];
    uint32_t rom_size;
    uint8_t *rom_data;
    rom_header *header;
} cart_context;

static cart_context ctx;

static void printchars(char *str, uint8_t len) {
    for (int i = 0; i < len; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

static uint8_t checksum() {
    uint16_t checksum = 0;
    for (int i = 0x0A0; i < 0x0BC; i++) {
        checksum = checksum - ctx.rom_data[i];
    }
    return ((checksum - 0x19) & 0xFF);
}

bool cart_load(char *cart) {
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

    FILE *fp = fopen(cart, "r");
    if (!fp) {
        printf("Failed to open ROM...\n");
        return false;
    }

    printf("Opened: %s...\n", ctx.filename);

    fseek(fp, 0, SEEK_END);
    ctx.rom_size = ftell(fp);
    rewind(fp);

    ctx.rom_data = malloc(ctx.rom_size);
    fread(ctx.rom_data, ctx.rom_size, 1, fp);
    fclose(fp);

    ctx.header = (rom_header *)(ctx.rom_data);
    printf("Title: ");
    printchars(ctx.header->title, (uint8_t) sizeof(ctx.header->title));
    printf("Game Code: ");
    printchars(ctx.header->game_code, (uint8_t) sizeof(ctx.header->game_code));
    printf("Maker Code: ");
    printchars(ctx.header->maker_code, (uint8_t) sizeof(ctx.header->maker_code));
    printf("ROM Size: %dKB\n", ctx.rom_size/(1024 * 1024));
    printf("ROM Version: %d\n", ctx.header->version);

    
    printf("Checksum: %s\n", checksum() == ctx.header->checksum ? "OK" : "BAD");

    return true;
}