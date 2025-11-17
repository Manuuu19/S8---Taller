#include <stdio.h>

#define MAX_PRODUCTOS 5
#define LARGO_NOMBRE 50

int sonIguales(char texto1[], char texto2[]);
void copiarTexto(char destino[], char fuente[]);
int buscarProductoPorNombre(char nombreBuscado[], char nombres[][LARGO_NOMBRE], int numProductos);

void ingresarProducto(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int *numProductosActuales);
void editarProducto(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int numProductosActuales);
void eliminarProducto(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int *numProductosActuales);
void mostrarProductos(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int numProductosActuales);

void calcularFactibilidad(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int numProductosActuales);

int main() {
    char nombres[MAX_PRODUCTOS][LARGO_NOMBRE];
    float tiemposUnitarios[MAX_PRODUCTOS];
    float recursosUnitarios[MAX_PRODUCTOS];
    int numProductosActuales = 0;
    int opcion = 0;

    printf("--- Bienvenido al Sistema de Factibilidad de Produccion ---\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("Productos actuales: %d de %d\n", numProductosActuales, MAX_PRODUCTOS);
        printf("1. Ingresar nuevo producto\n");
        printf("2. Editar producto existente\n");
        printf("3. Eliminar producto\n");
        printf("4. Calcular Factibilidad de Produccion\n");
        printf("5. Mostrar todos los productos\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarProducto(nombres, tiemposUnitarios, recursosUnitarios, &numProductosActuales);
                break;
            case 2:
                editarProducto(nombres, tiemposUnitarios, recursosUnitarios, numProductosActuales);
                break;
            case 3:
                eliminarProducto(nombres, tiemposUnitarios, recursosUnitarios, &numProductosActuales);
                break;
            case 4:
                calcularFactibilidad(nombres, tiemposUnitarios, recursosUnitarios, numProductosActuales);
                break;
            case 5:
                mostrarProductos(nombres, tiemposUnitarios, recursosUnitarios, numProductosActuales);
                break;
            case 6:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}

int sonIguales(char texto1[], char texto2[]) {
    int i = 0;
    while (texto1[i] == texto2[i]) {
        if (texto1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return 1;
}

void copiarTexto(char destino[], char fuente[]) {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
    }
    destino[i] = '\0';
}

int buscarProductoPorNombre(char nombreBuscado[], char nombres[][LARGO_NOMBRE], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (sonIguales(nombreBuscado, nombres[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void ingresarProducto(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int *numProductosActuales) {
    
    if (*numProductosActuales >= MAX_PRODUCTOS) {
        printf("Error: Inventario lleno. No se pueden agregar mas productos.\n");
        return;
    }

    printf("\n--- Ingreso de Nuevo Producto ---\n");
    int indice = *numProductosActuales;

    printf("Nombre del producto %d: ", indice + 1);
    scanf("%s", nombres[indice]);

    printf("Tiempo de fabricacion (en horas) para %s: ", nombres[indice]);
    scanf("%f", &tiempos[indice]);

    printf("Recursos (en unidades) para %s: ", nombres[indice]);
    scanf("%f", &recursos[indice]);

    (*numProductosActuales)++; 
    
    printf("Producto '%s' agregado exitosamente.\n", nombres[indice]);
}

void editarProducto(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int numProductosActuales) {
    char nombreBuscado[LARGO_NOMBRE];
    printf("\n--- Editar Producto ---\n");
    
    if (numProductosActuales == 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombreBuscado);

    int indice = buscarProductoPorNombre(nombreBuscado, nombres, numProductosActuales);

    if (indice == -1) {
        printf("Error: Producto '%s' no encontrado.\n", nombreBuscado);
    } else {
        printf("Editando producto '%s'.\n", nombres[indice]);
        
        printf("Nuevo tiempo de fabricacion (actual %.2f): ", tiempos[indice]);
        scanf("%f", &tiempos[indice]);

        printf("Nuevos recursos (actual %.2f): ", recursos[indice]);
        scanf("%f", &recursos[indice]);

        printf("Producto '%s' actualizado.\n", nombres[indice]);
    }
}

void eliminarProducto(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int *numProductosActuales) {
    char nombreBuscado[LARGO_NOMBRE];
    printf("\n--- Eliminar Producto ---\n");

    if (*numProductosActuales == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombreBuscado);

    int indice = buscarProductoPorNombre(nombreBuscado, nombres, *numProductosActuales);

    if (indice == -1) {
        printf("Error: Producto '%s' no encontrado.\n", nombreBuscado);
    } else {
        for (int j = indice; j < (*numProductosActuales) - 1; j++) {
            copiarTexto(nombres[j], nombres[j + 1]);
            tiempos[j] = tiempos[j + 1];
            recursos[j] = recursos[j + 1];
        }

        (*numProductosActuales)--; 
        
        printf("Producto '%s' eliminado exitosamente.\n", nombreBuscado);
    }
}

void mostrarProductos(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int numProductosActuales) {
    printf("\n--- Listado de Productos en Sistema ---\n");

    if (numProductosActuales == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("Indice | Nombre\t | Tiempo (h) | Recursos (u)\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < numProductosActuales; i++) {
        printf("%-6d | %-10s | %-10.2f | %-12.2f\n", i, nombres[i], tiempos[i], recursos[i]);
    }
}

void calcularFactibilidad(char nombres[][LARGO_NOMBRE], float tiempos[], float recursos[], int numProductosActuales) {
    printf("\n--- Calculo de Factibilidad de Produccion ---\n");
    
    if (numProductosActuales == 0) {
        printf("Debe ingresar productos antes de calcular la factibilidad.\n");
        return;
    }

    int demanda[MAX_PRODUCTOS];
    float tiempoTotalRequerido = 0;
    float recursosTotalesRequeridos = 0;
    float tiempoDisponible, recursosDisponibles;

    printf("Ingrese la demanda para cada producto:\n");
    for (int i = 0; i < numProductosActuales; i++) {
        printf("Cantidad demandada de '%s': ", nombres[i]);
        scanf("%d", &demanda[i]);
    }

    printf("\nIngrese los limites de la fabrica:\n");
    printf("Tiempo total disponible (en horas): ");
    scanf("%f", &tiempoDisponible);
    printf("Recursos totales disponibles (en unidades): ");
    scanf("%f", &recursosDisponibles);

    for (int i = 0; i < numProductosActuales; i++) {
        tiempoTotalRequerido += tiempos[i] * demanda[i];
        recursosTotalesRequeridos += recursos[i] * demanda[i];
    }

    printf("\n--- REPORTE DE FACTIBILIDAD ---\n");
    printf("Tiempo Total Requerido: \t%.2f horas\n", tiempoTotalRequerido);
    printf("Tiempo Total Disponible: \t%.2f horas\n", tiempoDisponible);
    printf("Recursos Totales Requeridos: \t%.2f unidades\n", recursosTotalesRequeridos);
    printf("Recursos Totales Disponibles: \t%.2f unidades\n", recursosDisponibles);
    printf("---------------------------------------------\n");

    if (tiempoTotalRequerido <= tiempoDisponible && recursosTotalesRequeridos <= recursosDisponibles) {
        printf("==> CONCLUSION: La produccion ES FACTIBLE.\n");
    } else {
        printf("==> CONCLUSION: La produccion NO ES FACTIBLE.\n");
        if (tiempoTotalRequerido > tiempoDisponible) {
            printf("    MOTIVO: Deficit de %.2f horas de tiempo.\n", tiempoTotalRequerido - tiempoDisponible);
        }
        if (recursosTotalesRequeridos > recursosDisponibles) {
            printf("    MOTIVO: Deficit de %.2f unidades de recursos.\n", recursosTotalesRequeridos - recursosDisponibles);
        }
    }
}