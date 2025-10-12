# Lab 3
Topic: Game of life

Student: Stanisalv Ciobanu

Group: I2302

Teacher: V.Trebes

# How to run
Run ```./run.ps1``` in command line

# Structure

Project contains field structure and methods to create and print field:
```C
typedef struct field {
    int width;
    int height;
    char* values;
} field;

void clear_screen() {
    ...
}

field* field_ctor(int width, int height) {
    field* f = (field*)malloc(sizeof(field));
    f->width = width;
    f->height = height;
    f->values = (char*)calloc(width * height, sizeof(char));
    return f;
}

void print_field(field* f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            printf("%c ", f->values[y * f->width + x] ? '*' : '.');
        }
        printf("\n");
    }
}
```

Contains core algorithm logic methods for implementing the game of life:
```C
int count_alive_neighbours(field* f, int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < f->width && ny >= 0 && ny < f->height)
                count += f->values[ny * f->width + nx];
        }
    }
    return count;
}

void step(field* f) {
    char* new_values = (char*)calloc(f->width * f->height, sizeof(char));
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            int alive = f->values[y * f->width + x];
            int n = count_alive_neighbours(f, x, y);
            if (alive && (n == 2 || n == 3))
                new_values[y * f->width + x] = 1;
            if (!alive && n == 3)
                new_values[y * f->width + x] = 1;
        }
    }
    free(f->values);
    f->values = new_values;
}
```

And contains four prepaired patterns:
```C
void add_toad(field* f) {
    ...
}

void add_glider(field* f) {
    ...
}

void add_blinker(field* f) {
    ...
}

void add_block(field* f) {
    ...
}

int main(void) {
    field* f = field_ctor(30, 30);
    
    //add_toad(f);
    //add_blinker(f);
    add_glider(f);
    //add_block(f);

    while (1) {
        clear_screen();
        print_field(f);
        step(f);
        sleep(1);
    }

    free(f->values);
    free(f);
    return 0;
}
```