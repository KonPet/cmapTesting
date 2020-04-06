#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>
#include <simplenfl.h>

int main(int argc, char **argv) {
    NF_Set2D(0, 0);
    NF_SetRootFolder("NITROFS");
    consoleDemoInit();
    consoleClear();

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);

//    loadsprite(0, 0, 0, 8, 8, "blue", "colors", false);
//    loadsprite(0, 1, 1, 8, 8, "green", "colors", false);
//    loadsprite(0, 2, 2, 8, 8, "red", "colors", false);

    loadsprite(0, 0, 0, 8, 8, "player", "player", false);

    NF_InitCmapBuffers();
    NF_LoadColisionMap("cmap", 0, 512, 520);

    loadbg("background", "background", 512, 512, 0, 3);

    int playerX = 12;
    int playerY = 12;
    int vel = 1;

    int offsetX = 0;
    int offsetY = 0;

    int wall = 1;

    NF_CreateSprite(0, 0, 0, 0, playerX, playerY);

	while(1) {
        if (ispressed("LEFT", "held")) {
            if (NF_GetTile(0, playerX + offsetX - vel, playerY + offsetY) != wall &&
                NF_GetTile(0, playerX + offsetX - vel, playerY + offsetY + 7) != wall) playerX -= vel;
        }
        if (ispressed("UP", "held")) {
            if (NF_GetTile(0, playerX + offsetX, playerY + offsetY - vel) != wall &&
                NF_GetTile(0, playerX + offsetX + 7, playerY + offsetY - vel) != wall) playerY -= vel;
        }
	    if (ispressed("RIGHT", "held")) {
	        if (NF_GetTile(0, playerX + offsetX + 7 + vel, playerY + offsetY) != wall &&
                NF_GetTile(0, playerX + offsetX + 7 + vel, playerY + offsetY + 7) != wall) playerX += vel;
	    }
	    if (ispressed("DOWN", "held")) {
            if (NF_GetTile(0, playerX + offsetX, playerY + offsetY + 7 + vel) != wall &&
                NF_GetTile(0, playerX + offsetX + 7, playerY + offsetY + 7 + vel) != wall) playerY += vel;
	    }

        if (ispressed("Y", "held")) {
            vel = 2;
        } else {
            vel = 1;
        }

        while (playerY > 160 && offsetY < 320) {
            offsetY++;
            playerY--;
            NF_ScrollBg(0, 3, offsetX, offsetY);
        }
        while (playerY < 24 && offsetY > 0) {
            offsetY--;
            playerY++;
            NF_ScrollBg(0, 3, offsetX, offsetY);
        }

        while (playerX < 24 && offsetX > 0) {
            offsetX--;
            playerX++;
            NF_ScrollBg(0, 3, offsetX, offsetY);
        }
        while (playerX > 224 && offsetX < 256) {
            offsetX++;
            playerX--;
            NF_ScrollBg(0, 3, offsetX, offsetY);
        }

	    NF_MoveSprite(0, 0, playerX, playerY);

	    NF_SpriteOamSet(0);
        swiWaitForVBlank();
        oamUpdate(&oamMain);
	}

	return 0;

}
