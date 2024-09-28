DROP DATABASE IF EXISTS Juego;
CREATE DATABASE Juego;
USE Juego;

-- Tabla Jugador
CREATE TABLE Jugador (
  Nombre_de_usuario VARCHAR(10) PRIMARY KEY NOT NULL,
  Contraseña VARCHAR(255) NOT NULL
) ENGINE=InnoDB;

-- Tabla Partida
CREATE TABLE Partida (
  ID_Partida INT AUTO_INCREMENT PRIMARY KEY,
  Ganador VARCHAR(10),
  Fecha_finalizacion DATE NOT NULL,
  Duracion INT NOT NULL,
  FOREIGN KEY (Ganador) REFERENCES Jugador(Nombre_de_usuario)
) ENGINE=InnoDB;

-- Tabla Participaciones
CREATE TABLE Participaciones (
  ID_Partida INT,
  Nombre_Jugador VARCHAR(10),
  Rol VARCHAR(10),
  FOREIGN KEY (Nombre_Jugador) REFERENCES Jugador(Nombre_de_usuario),
  FOREIGN KEY (ID_Partida) REFERENCES Partida(ID_Partida)
) ENGINE=InnoDB;

-- Insertar jugadores
INSERT INTO Jugador VALUES ('Valentino', 'contra1');
INSERT INTO Jugador VALUES ('Eloi', 'contra2');
INSERT INTO Jugador VALUES ('Nico', 'contra3');

-- Insertar partidas
INSERT INTO Partida (Ganador, Fecha_finalizacion, Duracion) VALUES ('Valentino', '2024-01-01', 60);
INSERT INTO Partida (Ganador, Fecha_finalizacion, Duracion) VALUES ('Eloi', '2024-02-01', 45);
INSERT INTO Partida (Ganador, Fecha_finalizacion, Duracion) VALUES ('Nico', '2024-03-01', 90);

INSERT INTO Participaciones (ID_Partida, Nombre_Jugador, Rol) VALUES (1, 'Valentino', 'Ganador');
INSERT INTO Participaciones (ID_Partida, Nombre_Jugador, Rol) VALUES (1, 'Eloi', 'Perdedor');
INSERT INTO Participaciones (ID_Partida, Nombre_Jugador, Rol) VALUES (2, 'Valentino', 'Ganador');
INSERT INTO Participaciones (ID_Partida, Nombre_Jugador, Rol) VALUES (2, 'Nico', 'Ganador');
INSERT INTO Participaciones (ID_Partida, Nombre_Jugador, Rol) VALUES (3, 'Valentino', 'Ganador');
INSERT INTO Participaciones (ID_Partida, Nombre_Jugador, Rol) VALUES (3, 'Eloi', 'Perdedor');