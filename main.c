/*
  Dylan Roman Buitrago Gil
  PROF. Nixón Patiño
  Sec. 1
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 6
#define CARS_LENGTH 6

struct car
{
  char brand[20];
  int tank;
  bool automatic;
  float cityKm;
  float roadKm;
  float mixKm;
};

void initCars(struct car arr_car[MAX])
{
  char *arr_brand[CARS_LENGTH] = {"Aveo", "Aveo", "Spark", "Silverado", "Blazer", "Tahoe"};
  int arr_tank[CARS_LENGTH] = {45, 45, 35, 98, 68, 98};
  bool arr_automatic[CARS_LENGTH] = {false, true, false, true, true, true};
  float arr_cityKm[CARS_LENGTH] = {17.38, 16.62, 18.23, 8.21, 9.96, 7.51};
  float arr_roadKm[CARS_LENGTH] = {23.65, 24.05, 26.51, 13.07, 15.81, 12.49};
  float arr_mixKm[CARS_LENGTH] = {19.74, 19.31, 21.20, 9.86, 11.94, 9.15};

  for (int i = 0; i < CARS_LENGTH; i++)
  {
    struct car element;

    strcpy(element.brand, arr_brand[i]);
    element.tank = arr_tank[i];
    element.automatic = arr_automatic[i];
    element.cityKm = arr_cityKm[i];
    element.roadKm = arr_roadKm[i];
    element.mixKm = arr_mixKm[i];

    arr_car[i] = element;
  }
}

void showTableCar(struct car arr_car[])
{
  printf("      \t         \t\t       \tConsumo de Km por Litros\n");
  printf("Modelo\tTrasmision\t\tTanque\tCiudad\tCarretera\tMixto\n");

  for (int i = 0; i < MAX; i++)
  {
    char trans_type[20];

    if (arr_car[i].automatic)
    {
      strcpy(trans_type, "Automatico");
    }
    else
    {
      strcpy(trans_type, "Manual  ");
    }

    printf(
        "%s\t%s\t\t%dlts\t%0.2f\t%0.2f\t%0.2f\n",
        arr_car[i].brand,
        trans_type,
        arr_car[i].tank,
        arr_car[i].cityKm,
        arr_car[i].roadKm,
        arr_car[i].mixKm);
  }
}

void showOptions()
{
  printf("1) Mostrar tabla de carros disponibles\t 2) Registrar la entrada de un carro\t 3) Salir\n");
}

struct car findCar(struct car arr_car[], char new_brand[20], bool automatic)
{
  bool isSame = true;

  for (int i = 0; i < CARS_LENGTH; i++)
  {
    int j = 0;
    struct car this_car = arr_car[i];
    char car_brand[20];

    while (this_car.brand[j])
    {
      car_brand[j] = toupper(this_car.brand[j]);
      if (car_brand[j] == new_brand[j] && isSame)
      {
        isSame = true;
      }
      else
      {
        isSame = false;
      }

      j++;
    }

    if (isSame == true)
    {
      if (this_car.automatic == automatic)
      {
        return this_car;
      }
    }
  }
}

int main()
{
  char name[50];
  int option;
  struct car arr_car[MAX];
  initCars(arr_car);

  printf("\nPor favor ingrese su nombre\n");
  gets(name);
  printf("Bienvenido %s, Que desea hacer\n", name);

  while (option != 3)
  {
    showOptions();
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      showTableCar(arr_car);
      break;

    case 2:
      int j = 0;
      char customer_name[50];
      int way_option = 0;
      double kilm = 0.00;
      double add_gas = 0.00;
      double total_gas = 0.00;
      double max_gas = 0.00;
      char car_trans[15];
      char brand[20];
      int finded_cars = 0;
      char new_brand[20];
      int index_cars[2];
      struct car car;
      bool wrongValue = true;
      bool report_car = false;

      printf("Ingrese nombre del cliente:\n");
      scanf(" %s", &customer_name);

      printf("Ingrese el modelo: ");
      scanf("%s", &brand);

      while (brand[j])
      {
        new_brand[j] = toupper(brand[j]);
        j++;
      }

      for (int i = 0; i < CARS_LENGTH; i++)
      {
        struct car this_car = arr_car[i];
        char car_brand[20];
        bool isSame = true;

        j = 0;

        while (this_car.brand[j])
        {
          car_brand[j] = toupper(this_car.brand[j]);
          if (car_brand[j] == new_brand[j] && isSame)
          {
            isSame = true;
          }
          else
          {
            isSame = false;
          }

          j++;
        }

        if (isSame)
        {
          car = arr_car[i];
          finded_cars++;
        }
      }

      if (finded_cars <= 0)
      {
        printf("Lo sentimos, No tenemos esa modelo de carro\n");
      }
      else
      {
        if (finded_cars > 1)
        {
          int transmision_type;
          wrongValue = true;

          while (wrongValue)
          {
            printf("Cual es el tipo de la transmision:\n1) Automatica\t2) Manual\n");
            scanf("%d", &transmision_type);

            if (transmision_type != 1 && transmision_type != 2)
            {
              printf("Valor incorrecto, intente de nuevo\n");
            }
            else
            {
              if (transmision_type == 1)
              {
                car = findCar(arr_car, new_brand, true);
                wrongValue = false;
              }
              else if (transmision_type == 2)
              {
                car = findCar(arr_car, new_brand, false);
                wrongValue = false;
              }
            }
          }
        }

        printf("Ingrese el Kilometraje:\n");
        scanf("%lf", &kilm);

        wrongValue = true;

        printf("Ingrese el tipo de recorrido\n1) Ciudad\t2) Carretera\t3) Mixto\n");

        while (wrongValue)
        {
          scanf("%d", &way_option);

          switch (way_option)
          {
          case 1:
            max_gas = (kilm * car.cityKm) + ((kilm * car.cityKm) * 0.10);
            wrongValue = false;
            break;

          case 2:
            max_gas = (kilm * car.cityKm) + ((kilm * car.cityKm) * 0.10);
            wrongValue = false;
            break;

          case 3:
            max_gas = (kilm * car.cityKm) + ((kilm * car.cityKm) * 0.10);
            wrongValue = false;
            break;
          
          default:
            printf("Por favor ingrese un valor correcto\n");
            break;
          }
        }

        printf("Ingrese gasolina adiciónal:\n");
        scanf("%lf", &add_gas);

        total_gas = add_gas + car.tank;
        printf("Max Gas: %0.2lf\n", max_gas);

        if(add_gas > 0) {
          printf("Gas Consumido:%0.2lf\n", total_gas);
        } else {
          printf("Gas Consumido: No mas de %0.2lf\n", total_gas);
        }

        if (total_gas > max_gas && add_gas > 0)
        {
          printf("\nEl vehiculo sera reportado\n\n");
          report_car = true;
        }

        if(car.automatic) {
          strcpy(car_trans, "Automatico");
        } else {
          strcpy(car_trans, "Manual");
        }


          printf(" __________________________");
          printf("\n|         REPORTE          |\n");
          printf("|__________________________|\n");
          printf("Usuario: %s\n", name);
          printf("Cliente: %s\n", customer_name);
          if (total_gas < 0)
          {
            printf(
              "%s\t %s \t %0.2lflts\t\n",
              car.brand,
              car_trans,
              car.tank
              );
          } else {
            printf(
              "%s\t %s \t %0.2lflts\t\n",
              car.brand,
              car_trans,
              total_gas
              );
          }

          if (report_car){
            printf("Carro Reportado\n\n");
          } else {
            printf("\n\n");
          }
        
      }

      break;

    case 3:
      printf("Hasta luego, vuelva pronto\n");
      break;

    default:
      printf("Por favor ingrese un valor correcto\n");
      showOptions();
      scanf("%d", &option);
      break;
    }
  };

  return 0;
}