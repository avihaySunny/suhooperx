#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
/* -------------------- */
#define TO_STRING_OBJ (0)
#define SAYSHELLO_ANIMAL (1)
#define  NUM_MASTERS (2)
#define TO_STRING_ANIM (3)
#define CLEAN_BUFFER (memset(global_string, 0, 1024))
typedef struct class metadata_t;
typedef void (*vtable_func)();
char global_string[1024] = {0}; 
/*------------------------------------------------------ */
struct class {
    char *name; 
    size_t size; 
    vtable_func (*table)[];  
    metadata_t *super; 
};
/*-----------------Object Class-------------------------- */
typedef struct object {
    metadata_t *class_identifer; 
}obj_t; 

char *toString(obj_t *this){
    CLEAN_BUFFER;
    sprintf(global_string, "%s %p", this->class_identifer->name, (void*)this);  
    return global_string;
}

vtable_func table_ref[] = {(vtable_func)toString};

metadata_t class_obj = {"Object", 
                        sizeof(obj_t),
                        &table_ref,    
                        NULL};

void ObjCntr(obj_t *this){
    (void)this;
}
/*------------------------------------------------------ */
 obj_t *Alloc(metadata_t *class_identifier)
{
    obj_t *tmp = (obj_t*)calloc(1, class_identifier->size);
    if (tmp == NULL){
        return NULL;
    }

    tmp->class_identifer = class_identifier;
    return tmp;
}
/*------------------ANIMAL---------------------------- */
typedef struct animal { 
    obj_t object;
    int num_legs;
	int num_masters;
	int ID;
}animal_t;
/* global counter  */
int static_animal_counter = 0;

void AnimalsaysHello(animal_t *this);
int AnimalgetNumMaster(animal_t *this);
char* AnimalToString(animal_t *this);
void AnimalShowsCounter(); 
/*function vector for animal */

 vtable_func animal_table_ref[] = {   (vtable_func)toString, 
                                        (vtable_func)AnimalsaysHello,
                                        (vtable_func)AnimalgetNumMaster, 
                                        (vtable_func)AnimalToString };
metadata_t class_animal = {"Animal", 
                            sizeof(animal_t),
                            &animal_table_ref, 
                            &class_obj};

void AnimalConstructor1(animal_t *this){
    this->object.class_identifer = &class_animal;
    this->num_legs = 5;  
    this->num_masters =  1; 
    this->ID = ++static_animal_counter;
    
    printf("Animal Ctor\n");
     (((*(this->object.class_identifer->table))[SAYSHELLO_ANIMAL]))(this);
    AnimalShowsCounter();
     (((*(this->object.class_identifer->table))[NUM_MASTERS]))(this);
    printf("%s\n", ((char*(*)(animal_t*)) ((*(this->object.class_identifer->table))[TO_STRING_ANIM]))(this));
    CLEAN_BUFFER;
    printf("%s\n",((char*(*)(obj_t*))(*(this->object.class_identifer->table))[TO_STRING_OBJ])((obj_t*)this));

}

void AnimalConstructor2(animal_t *this, int num_masters){
    AnimalConstructor1(this); 
    this->num_masters = num_masters;  
}
/*--------------ANIMAL METHODS------------------------------- */
void staticDeclarationsAnimal(){
    printf("Static block Animal 1\n");
    printf("Static block Animal 2\n");
    printf("Instance initialization block Animal\n");
}

void staticDeclAnim2(){
     printf("Instance initialization block Animal\n");
}
/* method 1 */
void AnimalsaysHello(animal_t *this)
{
    printf("%s Hello\n", this->object.class_identifer->name);
    printf("I have %d legs\n", this->num_legs); 
}
/* method 2*/
void AnimalShowsCounter(){
    printf("%d \n", static_animal_counter);
}
/* method 3 */
int AnimalgetNumMaster(animal_t *this){
    return this->num_masters;
}
/* method 4 */
char* AnimalToString(animal_t *this){
    CLEAN_BUFFER;
    sprintf(global_string,"%s With ID : %d", this->object.class_identifer->name, this->ID); 
    return global_string;
}

void foo(animal_t *this){
    printf("%s\n",((char*(*)(obj_t*))(*(this->object.class_identifer->table))[TO_STRING_ANIM])((obj_t*)this));
}

/*------------------DOG CLASS----------------------- */
typedef struct dog{
    animal_t animal; 
    int num_legs;  
    
}dog_t; 
void dogsaysHello(dog_t *thisdawg);
char *dogToString(dog_t *thisdawg);

vtable_func dog_table_ref[] = {(vtable_func)toString, 
                                (vtable_func)dogsaysHello,
                                (vtable_func)AnimalgetNumMaster, 
                                (vtable_func)AnimalToString,
                                (vtable_func)dogsaysHello, 
                                (vtable_func)dogToString};  

metadata_t class_dog = {"Dog", 
                        sizeof(dog_t),
                        &dog_table_ref, 
                        &class_animal};

void staticDogDeclarations(){
    printf("Static block dog\n");
    printf("Instance initialization block Dog\n");
} 


void staticDogDecl2(){
    puts("static block dog");
}

void DogConstructor(dog_t *thisdog){
    thisdog->animal.object.class_identifer = &class_dog;
    thisdog->num_legs = 4; 
    AnimalConstructor2(&thisdog->animal , 2);
    printf("DogCtor\n");
    
}

void dogsaysHello(dog_t *thisdawg){
    printf("Dog Hello wof wof!\n");
    printf("I Have this many (%d) legs\n", thisdawg->num_legs);
}

char* dogToString(dog_t *thisdawg){
    CLEAN_BUFFER; 
    sprintf(global_string,"DOG With ID : %d\n", thisdawg->animal.ID); 
    
    return global_string;
} 
/*------------------CAT CLASS----------------------- */
 typedef struct cat{
    animal_t animal;
    char *colors; 
    int num_masters; 
    
}cat_t; 

char* catToString(cat_t *thiscat){
    CLEAN_BUFFER; 
    sprintf(global_string,"CAT With ID : %d", thiscat->animal.ID); 
    
    return global_string;
}

vtable_func cat_table_ref[] = {(vtable_func)toString, 
                                (vtable_func)AnimalsaysHello,
                                (vtable_func)AnimalgetNumMaster, 
                                (vtable_func)AnimalToString,
                                (vtable_func)AnimalsaysHello,
                                (vtable_func)catToString};

metadata_t class_cat = {"Cat", 
                            sizeof(cat_t),
                            &cat_table_ref, 
                            &class_animal};

void staticCatDeclarations(){
    printf("Static block Cat\n");
}

void CatConstructor2(cat_t *this, char *color){
    this->animal.object.class_identifer = &class_cat;
    AnimalConstructor1(&this->animal);
    this->colors = color; 
    printf("Cat Ctor with color %s\n", this->colors);
}

void catConstructor1(cat_t *this){
    this->animal.object.class_identifer = &class_cat;
    CatConstructor2(this, "black"); 
    printf("CatCTOR\n"); 
    this->num_masters = 2; 
}
/* -----------THISISLEGENDARYANIMAL-------------- */
typedef struct LegendaryAnimal{
    cat_t cat; 
}lg_animal_t;

char * LGtoString(lg_animal_t *lg_animal){
    CLEAN_BUFFER; 
    sprintf(global_string,"LegendaryANimal With ID : %d", lg_animal->cat.animal.ID); 
    
    return global_string;
}

void LgSaysHello(lg_animal_t *this){
    printf("HELLO I AM LEGENDARYYYY");
    (void)this;
}

void staticLegendaryDeclartions(){
    puts("Static block Legendary Animal");
    puts("Instance initialization block Animal");
}
vtable_func lg_table_ref[] = {(vtable_func)LGtoString, (vtable_func)LgSaysHello};

metadata_t class_legendary = {"LegendaryAnimal", 
                              sizeof(lg_animal_t),  
                              &lg_table_ref, 
                              &class_cat};
void LegendaryConstructor(lg_animal_t *this){
    this->cat.animal.object.class_identifer = &class_legendary;
    catConstructor1(&this->cat);
    puts("Legendary Cstor");
}
/*----------------------Main------------------------ */
int main(void){
    int i; 
    animal_t *animal1;
    animal_t *ark[5] = {NULL};
    cat_t *cat; 
    dog_t *dog; 
    /*ark animals */
    dog_t *dogForArr; 
    cat_t *catForArr;
    cat_t *blackCatForArr;
    lg_animal_t *legendaryAnimalforArr;
    animal_t *animalForArr; 
    /*-------------------- */

    lg_animal_t *myDragon; 
    staticDeclarationsAnimal();
    animal1 =(animal_t*)Alloc(&class_animal);
    dog = (dog_t*)Alloc(&class_dog);   
    AnimalConstructor1(animal1);
    staticDogDeclarations();
    staticDogDecl2();
    puts("-----------------");
    DogConstructor(dog); 
    puts ("----------------");
    cat = (cat_t*)Alloc(&class_cat);
    catConstructor1(cat);
    cat->animal.object.class_identifer = &class_cat;
    printf("%s\n",((char*(*)(cat_t*))((*(cat->animal.object.class_identifer->table))[5]))(cat));

    puts ("----------------");
    myDragon = (lg_animal_t*)Alloc(&class_legendary);
    staticLegendaryDeclartions(); 
    LegendaryConstructor(myDragon); 
    /*------------------------- */
 puts("------------------------");
    AnimalShowsCounter(); 
    printf("%d\n", animal1->ID); 
    printf("%d\n", dog->animal.ID); 
    printf("%d\n", cat->animal.ID);
    printf("%d\n", myDragon->cat.animal.ID); 
    staticDeclAnim2();
    staticDogDeclarations();
    puts("-----------------------");
    dogForArr = (dog_t*)Alloc(&class_dog);
    DogConstructor(dogForArr);
    catForArr = (cat_t*)Alloc(&class_cat);
    catConstructor1(catForArr); 
    blackCatForArr = (cat_t*)Alloc(&class_cat);
    CatConstructor2(blackCatForArr, "white");
    legendaryAnimalforArr = (lg_animal_t*)Alloc(&class_legendary);
    LegendaryConstructor(legendaryAnimalforArr);
    animalForArr = (animal_t*)Alloc(&class_animal);
    AnimalConstructor1(animalForArr);   
    /*----------------------------------- */

    puts("-----------------------");
    ark[0] = (animal_t*)dogForArr; 
    ark[1] = (animal_t*)catForArr;
    ark[2] = (animal_t*)blackCatForArr;
    ark[3] = (animal_t*)legendaryAnimalforArr;
    ark[4] = (animal_t*)animalForArr; 
    
    catForArr->animal.object.class_identifer = &class_animal;
    blackCatForArr->animal.object.class_identifer = &class_animal;

    for (i = 0; i < 5; ++i){
        ((*(ark[i]->object.class_identifer->table))[1])(ark[i]);
        printf("%d\n",ark[i]->num_masters);   
    }

    catForArr->animal.object.class_identifer = &class_cat;
    blackCatForArr->animal.object.class_identifer = &class_cat;

    for (i = 0; i < 5; ++i){
        foo(ark[i]);
    }

    return EXIT_SUCCESS;
}
