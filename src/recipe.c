
typedef struct {
  char *name;
  int instructions_len;
  char *instructions[16];
  int servings_len;
  Serving servings[16];
} RecipePart;

typedef struct {
  char *name;
  char *type;
  char *portions;
  char *description;
  int date;
  int time;
  int parts_len;
  RecipePart *parts[10];
} Recipe;

Recipe create_recipe(char *name, char *type, char *portions, int date, int time) {
  Recipe a;
  a.name = name;
  a.type = type;
  a.portions = portions;
  a.date = date;
  a.time = time;
  a.parts_len = 0;
  return a;
}

RecipePart create_part(char *name) {
  RecipePart a;
  a.name = name;
  a.instructions_len = 0;
  a.servings_len = 0;
  return a;
}

void set_description(Recipe *r, char *description){
  r->description = description;
}

void add_instruction(RecipePart *p, char *instruction){
  p->instructions[p->instructions_len] = instruction;
  p->instructions_len++;
}

void add_serving(RecipePart *p, Ingredient *i, char *quantity){
  p->servings[p->servings_len] = create_serving(i,quantity);
  p->servings_len++;
}

void add_part(Recipe *r, RecipePart *p){
  r->parts[r->parts_len] = p;
  r->parts_len++;
}

void print_recipe(Recipe *recipe) {
  printf("name:%s(%s), portions:%s date:%d time:%d\n",recipe->name,recipe->type,recipe->portions,recipe->date,recipe->time);
  printf("===========\nParts:\n");
  for(int i = 0; i < recipe->parts_len; ++i) {
    printf("-- %s(%d ingredients %d instructions)\n", recipe->parts[i]->name, recipe->parts[i]->servings_len, recipe->parts[i]->instructions_len);
    for(int i2 = 0; i2 < recipe->parts[i]->instructions_len; ++i2) {
      printf("---- %s\n", recipe->parts[i]->instructions[i2]);
    }
    for(int i2 = 0; i2 < recipe->parts[i]->servings_len; ++i2) {
      printf("------ %s\n", recipe->parts[i]->servings[i2].ingredient->name);
    }
  }
  // printf("===========\nIngredients:\n");
  // for(int i = 0; i < recipe.servings_len; ++i) {
  //   printf("%s %s\n", recipe.servings[i].ingredient->name,recipe.servings[i].quantity);
  // }
}

void build_recipe_page(Recipe *recipe){
  char recipe_path[1024];
  to_lowercase(recipe->name, recipe_path);

  char recipe_filepath[1024];
  sprintf(recipe_filepath, "../site/%s.html", recipe_path);

  printf("%s -> %s\n", recipe->name, recipe_filepath);

  FILE *myfile = fopen(recipe_filepath, "w");

  fprintf(myfile, "<h1>%s</h1>\n", recipe->name);
  for(int i = 0; i < recipe->parts_len; ++i) {
    fprintf(myfile, "<h2>%s</h2>\n", recipe->parts[i]->name);
    fputs("<ul>\n", myfile);
    for(int i2 = 0; i2 < recipe->parts[i]->instructions_len; ++i2) {
      fprintf(myfile, "<li>%s</li>\n", recipe->parts[i]->instructions[i2]);
    }
    fputs("</ul>\n", myfile);
  // fputs("<ul>", myfile);
  //   fputs("<li>", myfile);
  //   fputs(recipe->parts[i]->name, myfile);
  //   fputs("</li>", myfile);
  }
  // fputs("</ul>", myfile);

  // fprintf(myfile, "%s!\n", recipe_path);

  fclose(myfile);
}