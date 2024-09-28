
// Consulta para obtener el porcentaje de victorias de un jugador dado
#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

int main() {
    char nombre[20];  
    char consulta[256];  // Buffer para las consultas SQL
    MYSQL *conn;
    MYSQL_RES *resultado;
    MYSQL_ROW row;
    int err;
    
    // Conectar a la base de datos (basado en apartado 3 de atenea)
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error al inicializar la conexión\n");
        return 1;
    }
    
    if (mysql_real_connect(conn, "localhost", "usuario", "contraseña", "Juego", 0, NULL, 0) == NULL) {
        printf("Error al conectar a la base de datos: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Solicitar el nombre del jugador
    printf("Introduce el nombre del jugador:\n");
    scanf("%s", nombre);  
    
    //Consulta para contar las participaciones del jugador
    sprintf(consulta, 
        "SELECT COUNT(*) FROM Participaciones WHERE Jugador = '%s'", 
        nombre);
    
    err = mysql_query(conn, consulta);
    if (err != 0) { 
        printf("Error al consultar las participaciones: %u %s\n", mysql_errno(conn), mysql_error(conn)); 
        mysql_close(conn);
        return 1; 
    } 

    resultado = mysql_store_result(conn);
    row = mysql_fetch_row(resultado);
    
    if (row == NULL || atoi(row[0]) == 0) {
        // Si no hay participaciones o el jugador no existe
        printf("No hay ningún jugador llamado %s o no ha participado en ninguna partida.\n", nombre);
        mysql_free_result(resultado);
        mysql_close(conn);
        return 1;
    }

    int total_participaciones = atoi(row[0]);  // Convertir el resultado a entero
    mysql_free_result(resultado);  // Liberar el resultado de la primera consulta

    //Consulta para contar las victorias del jugador
    sprintf(consulta, 
        "SELECT COUNT(*) FROM Partida WHERE Ganador = '%s'", 
        nombre);
    
    err = mysql_query(conn, consulta);
    if (err != 0) { 
        printf("Error al consultar las victorias: %u %s\n", mysql_errno(conn), mysql_error(conn)); 
        mysql_close(conn);
        return 1; 
    }

    resultado = mysql_store_result(conn);
    row = mysql_fetch_row(resultado);
    
    int total_victorias = atoi(row[0]);  // Convertir el resultado a entero
    mysql_free_result(resultado);  // Liberar el resultado de la segunda consulta

    //Calcular el porcentaje de victorias
    float porcentaje_victorias = ((float)total_victorias / total_participaciones) * 100;
    
    // Mostrar el resultado
    printf("El jugador %s ha participado en %d partidas y ha ganado %d partidas.\n", nombre, total_participaciones, total_victorias);
    printf("Porcentaje de victorias: %d\n", porcentaje_victorias);

    // Cerrar la conexión
    mysql_close(conn);

    return 0;
}


