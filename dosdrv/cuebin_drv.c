#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Simple structures for CUE/BIN track */
struct track {
    int number;
    long start;
    long length;
    int sector_size;
    int is_audio;
    FILE *file;
};

static struct track tracks[100];
static int track_count = 0;

static int parse_time(char *str)
{
    int m, s, f;
    if (sscanf(str, "%d:%d:%d", &m, &s, &f) != 3)
        return -1;
    return ((m * 60) + s) * 75 + f;
}

static int add_track(struct track *t)
{
    if (track_count >= 100)
        return -1;
    tracks[track_count++] = *t;
    return 0;
}

static int parse_cue(char *fname)
{
    FILE *f = fopen(fname, "r");
    char line[256];
    struct track curr;
    if (!f)
        return -1;
    memset(&curr, 0, sizeof(curr));
    while (fgets(line, sizeof(line), f)) {
        char cmd[32];
        char arg[128];
        char *p;
        if (sscanf(line, "%31s %127[^\n]", cmd, arg) < 1)
            continue;
        for (p = cmd; *p; ++p)
            *p = toupper(*p);
        if (!strcmp(cmd, "TRACK")) {
            if (curr.number)
                add_track(&curr);
            memset(&curr, 0, sizeof(curr));
            sscanf(arg, "%d", &curr.number);
            curr.sector_size = 2352;
        } else if (!strcmp(cmd, "INDEX")) {
            int idx;
            char time[32];
            sscanf(arg, "%d %31s", &idx, time);
            if (idx == 1)
                curr.start = parse_time(time);
        } else if (!strcmp(cmd, "FILE")) {
            char fn[128];
            char type[32];
            if (sscanf(arg, "\"%127[^\"]\" %31s", fn, type) >= 1)
                curr.file = fopen(fn, "rb");
        } else if (!strcmp(cmd, "PREGAP")) {
            /* ignore */
        }
    }
    if (curr.number)
        add_track(&curr);
    fclose(f);
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    if (argc < 2) {
        printf("Usage: cuebin_drv <image.cue>\n");
        return 1;
    }
    if (parse_cue(argv[1])) {
        printf("Failed to parse %s\n", argv[1]);
        return 1;
    }
    for (i = 0; i < track_count; ++i) {
        printf("Track %d start %ld\n", tracks[i].number, tracks[i].start);
    }
    return 0;
}
