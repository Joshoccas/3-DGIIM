-- CAPÍTULO 3: REALIZACIÓN DE CONSULTAS A UNA BD
-- 3.1 La sentencia de consulta SELECT
-- 3.2 La consulta en SQL y su relación con los operadores AR
-- 3.2.1 La proyección AR en SQL

/*Ejer 3.1 Comprueba el resultado de la proyección. ¿Es este conforme a lo que se obtiene
en el AR?*/
-- No porque repite valores. Opción correcta:
select distinct ciudad
from proyecto;
--ok

/*Ejer 3.2 Muestra los suministros realizados (tan solo los códigos de los componentes
de una venta). ¿Es necesario utilizar DISTINCT?*/
select codpj, codpro, codpie
from ventas;
--No es necesario usar distinct porque son PK => son únicas
--ok

-- 3.2.2 La selección AR en SQL

/*Ejer 3.3 Muestra las piezas de Madrid que son grises o rojas*/
select codpie
from pieza
where (ciudad='Madrid') and (color='Gris' or color='Rojo');
--ok

/*Ejer 3.4 Encontrar todos los suministros cuya cantidad está entre 200 y 300, ambos
inclusive*/
select codpie, codpro, codpj
from ventas
where (cantidad>=200 and cantidad<=300);

--sin usar and
select codpie, codpro, codpj
from ventas
where (cantidad between 200 and 300);

/*Ejer 3.5 Mostrar las piezas que contengan la palabra tornillo con la t en
mayúscula o en minúscula*/
select codpie
from pieza
where upper(nompie) like 'TORNILLO';

-- 3.2.3 Consultas sobre el catálogo
/*Ejer 3.6 Comprueba que no devuelve ninguna. Pero SÍ que hay!!!. Prueba a usar
la función upper() comparando con ’VENTAS’ o la función lower() comparando con
’ventas’. */
select table_name
from all_tables
where lower(TABLE_NAME) like '%ventas';

--3.2.4 Operadores AR sobre conjuntos en SQL

/*Ejer 3.7 Resolver la consulta del ejemplo 3.8 utilizando el operador interseccion*/ 
/*Ciudades donde viven proveedores con status mayor de 2 en las que no se fabrica
la pieza ’P1’. */

--ejemplo 3.8
(SELECT DISTINCT ciudad FROM proveedor WHERE status>2)
MINUS
(SELECT DISTINCT ciudad FROM pieza WHERE codpie='P1');

-- esta propuesta está mal porque puede coincidir la ciudad
-- de p1 y p2, y así cogerla
(select ciudad
from proveedor 
where status>2)
intersect
(select ciudad
from pieza
where codpie!='P1');

-- propuesta correcta:
(select ciudad
from proveedor
where status>2)
intersect
(select p1.ciudad
from proveedor p1, pieza p2
where p2.codpie='P1' and p1.ciudad!=p2.ciudad);
--ok

/*Ejer 3.8 Encontrar los códigos de aquellos proyectos a los que sólo abastece ’S1’. */
(select codpj
from ventas)
minus
(select distinct codpj
from ventas
where codpro != 'S1');
--ok

/*Ejer 3.9 Mostrar todas las ciudades de la base de datos. Utilizar UNION*/
(select ciudad
from proveedor) 
union
(select ciudad
from proyecto)
union
(select ciudad
from pieza);
--ok

/*Ejer 3.10 Mostrar todas las ciudades de la base de datos. Utilizar UNION ALL*/
(select ciudad
from proveedor)
union all 
(select ciudad
from proyecto)
union all
(select ciudad
from pieza);
--ok

-- 3.2.5 El producto cartesiano AR en SQL

/*Ejer 3.11 Comprueba cuántas tuplas resultan del producto cartesiano aplicado a ventas
y proveedor.*/
select *
from ventas, proveedor;
--217
select * from ventas;       --31
select * from proveedor;    --7
-- 31 x 7 = 217
--ok

/*Ejer 3.12 Mostrar las ternas que son de la misma ciudad pero que hayan realizado
alguna venta.*/
(select codpro, codpj, codpie
from ventas)
intersect
(select codpro, codpj, codpie
from proveedor, proyecto, pieza
where proveedor.ciudad=proyecto.ciudad
and proveedor.ciudad=pieza.ciudad);
--ok

--sin usar el intersect
(select codpro, codpj, codpie
from ventas)
minus
(select codpro, codpj, codpie
from proveedor, proyecto, pieza
where proveedor.ciudad!=proyecto.ciudad
or proveedor.ciudad!=pieza.ciudad);

--otra opción
select ventas.codpro, ventas.codpj, ventas.codpie
from proveedor, proyecto, pieza, ventas
where proveedor.ciudad=proyecto.ciudad
and proveedor.ciudad=pieza.ciudad
and proveedor.codpro=ventas.codpro
and pieza.codpie=ventas.codpie
and proyecto.codpj=ventas.codpj;

-- 3.2.6 El renombramiento o alias en SQl

/*Ejer 3.13 Encontrar parejas de proveedores que no viven en la misma ciudad*/
select A.codpro, B.codpro
from proveedor A, proveedor B
where A.ciudad > B.ciudad;
--NO usar el operador != porque duplica las parejas
--ok

/*Ejer 3.14 Encuentra las piezas con máximo peso.*/
(select codpie
from pieza)
minus
(select A.codpie
from pieza A, pieza B
where A.peso<B.peso);

-- 3.2.7 La equi-reunión y la reunión natural AR en SQL

/*Ejer 3.15 Mostrar las piezas vendidas por los proveedores de Madrid.*/
select distinct codpie
from ventas natural join (select codpro from proveedor where ciudad = 'Madrid');
--ok

--otra opción
select distinct codpie
from ventas
where codpro in (select codpro from proveedor where ciudad = 'Madrid');


/*Ejer 3.16 Encuentra la ciudad y los códigos de las piezas suministradas a cualquier
proyecto por un proveedor que está en la misma ciudad donde está el proyecto.*/
select distinct codpie, ciudad
from (pieza natural join    (select *
                             from ventas natural join  (select codpro,codpj
                                                        from proveedor natural join proyecto)));
--ok

--otra aproximación
select distinct pieza.ciudad, pieza.codpie
from ventas, pieza, proyecto, proveedor
where ventas.codpie=pieza.codpie and proyecto.ciudad=proveedor.ciudad
and proyecto.codpj=ventas.codpj and proveedor.codpro=ventas.codpro;


-- 3.3 Ordenación de resultados

/*Ejer 3.17 Comprobar la salida de la consulta anterior sin la cláusula ORDER BY.*/
select nompro
from proveedor;     --desordenados

select nompro
from proveedor
order by nompro;    --ordenados alfabéticamente

/*Ejer 3.18 Listar las ventas ordenadas por cantidad, si algunas ventas coinciden en la
cantidad se ordenan en función de la fecha de manera descendente*/
select *
from ventas
order by cantidad, fecha desc;

-- 3.4 Subconsultas en SQL
-- 3.4.1 IN, el operador de pertenencia

/*Ejer 3.19 Mostrar las piezas vendidas por los proveedores de Madrid. (Fragmentando
la consulta con ayuda del operador IN.) Compara la solución con la del ejercicio 3.15.*/
select distinct codpie
from ventas
where codpro in (select codpro from proveedor where ciudad='Madrid');
-- ok

/*Ejer 3.20 Encuentra los proyectos que están en una ciudad donde se fabrica alguna
pieza.*/
--Resolviendo con IN
select distinct codpj
from proyecto
where ciudad in (select ciudad from pieza);
--ok

--Resolviendo con reunión
select distinct codpj
from proyecto natural join pieza;

/*Ejer 3.21 Encuentra los códigos de aquellos proyectos que no utilizan ninguna pieza
roja que esté suministrada por un proveedor de Londres. */
(select codpj
from proyecto)
minus
(select codpj
from ventas
where codpie in (select codpie from pieza where color='Rojo') 
and codpro in (select codpro from proveedor where ciudad='Londres'));
--ok

--otro enfoque
(select codpj
from proyecto)
minus
(select codpj
from ventas, proveedor, pieza
where ventas.codpro = proveedor.codpro and ventas.codpie=pieza.codpie
and color='Rojo' and proveedor.ciudad='Londres');

-- 3.4.2 EXISTS, el operador de comprobación de existencia
-- 3.4.3 Otros operadores, los comparadores sobre conjuntos

/*Ejer 3.22 2 Muestra el código de las piezas cuyo peso es mayor que el peso de cualquier
’tornillo’. */
--otro enfoque
(select codpie
from pieza)
minus
(select p1.codpie
from pieza p1, pieza p2
where p1.peso <= p2.peso and p2.nompie = 'Tornillo');

--otro enfoque
select codpie from pieza where peso > all
(select peso from pieza where nompie = 'Tornillo');

/*Ejer 3.23 Encuentra las piezas con peso máximo. Compara esta solución con la obtenida
en el ejercicio 3.14*/
select codpie
from pieza p
where peso > all (select peso from pieza where codpie!=p.codpie);
--ok

--otro enfoque
select codpie
from pieza p
where peso >= all (select peso from pieza);


-- 3.5 La división AR en SQL
-- 3.5.1 Aproximación usando expresión equivalente en AR
-- 3.5.2 Aproximación basada en el Cálculo Relacional
-- 3.5.3 Aproximación mixta usando NOT EXISTS y la diferencia relacional

/*Ejer 3.24 Encontrar los códigos de las piezas suministradas a todos los proyectos
localizados en Londres*/
--Enfoque álgebra relacional
(select codpie from pieza)
minus
(select codpie
    from ((select pie.codpie, pj.codpj
           from pieza pie, proyecto pj
           where pj.ciudad='Londres')
           minus
           (select codpie, codpj
           from ventas))
);

--Enfoque cálculo relacional
select codpie from pieza pie
where not exists (select * from proyecto pj where ciudad='Londres' and
                  not exists (select * from ventas where codpie=pie.codpie and codpj=pj.codpj)
);
    

--Enfoque mixto
select codpie from pieza pie
where not exists ( (select codpj from proyecto pj where ciudad='Londres')
                    minus
                    (select codpj from ventas where codpie=pie.codpie)
);

/*Ejer 3.25 Ejercicio 3.25 Encontrar aquellos proveedores que envían piezas procedentes de todas las
ciudades donde hay un proyecto.*/

-- CREO QUE NO ESTÁ BIEN MI INTERPRETACIÓN
/* Mi interpretación es: encontrar aquellos proveedores que envían todas las piezas
que sean procedentes de alguna de las ciudades donde hay un proyecto*/
--Enfoque álgebra relacional
(select codpro from proveedor)
minus
(select codpro from ((select codpro,codpie
                    from proveedor, pieza
                    where pieza.ciudad in (select ciudad from proyecto))
                    minus
                    (select codpro,codpie
                    from ventas))
);

--Enfoque cálculo relacional
select codpro from proveedor pro
where not exists ( select * from pieza pie 
                   where pie.ciudad in (select ciudad from proyecto)
                                      and not exists (select * from ventas where codpro=pro.codpro and codpie=pie.codpie)
);

--Enfoque mixto
select codpro from proveedor pro
where not exists ( (select codpie from pieza
                    where pieza.ciudad in (select ciudad from proyecto))
                    minus
                   (select codpie from ventas
                    where codpro=pro.codpro)
);

-- EN CLASE:
SELECT  codpro FROM proveedor
WHERE NOT EXISTS (
    SELECT ciudad FROM proyecto
    MINUS
    SELECT ciudad FROM ventas NATURAL JOIN pieza
    WHERE ventas.codpro= proveedor.codpro);

-- 3.6 Funciones de agregación

/*Ejercicio 3.26 Encontrar el número de envíos con más de 1000 unidades.*/
select count (cantidad) --podemos sustituir 'cantidad' por '*'
from ventas
where cantidad>1000;
--ok

/*Ejer 3.27 Mostrar el máximo peso*/
select max(peso)
from pieza;
--ok

/*Ejer 3.28 Mostrar el código de la pieza de máximo peso. Compara esta solución con las
correspondientes de los ejercicios 3.14 y 3.23.*/
select codpie
from pieza
where peso = (select max(peso) from pieza);
--ok

/*Ejer 3.29 Comprueba si la siguiente sentencia resuelve el ejercicio anterior.*/
select codpie, max(peso)
from pieza; -- esta consulta FALLA
/* Las funciones AGREGAN los datos, obviando a partir de ahí
a qué instancia de entidad pertenecen.*/

/*Ejer 3.30 Muestra los códigos de proveedores que han hecho más de 3 envíos diferentes*/
select codpro
from proveedor p
where (select count(*) from ventas where codpro=p.codpro) > 3;
--ok
select codpro
from ventas
group by codpro
having count(codpro)>3;


--3.6.1 Formando grupos
/*Ejer 3.31 Mostrar la media de las cantidades vendidas por cada código de pieza junto
con su nombre.*/
select codpie, nompie, avg(cantidad)
from ventas natural join pieza
group by codpie, nompie;
--ok
-- NO podemos agrupar por nompie pq puede no ser único!

/*Ejer 3.32 Encontrar la cantidad media de ventas de la pieza ’P1’ realizadas por cada
proveedor.*/
select codpro, avg(cantidad)
from ventas
where codpie='P1'
group by codpro;
--ok

/*Ejer 3.33 Encontrar la cantidad total de cada pieza enviada a cada proyecto.*/
select codpie, codpj, sum(cantidad)
from ventas
group by codpie, codpj;
--ok

-- 3.6.2 Seleccionando grupos

/*Ejer 3.34 Comprueba si es correcta la solución anterior*/
select v.codpro, v.codpj, j.nompj, avg(v.cantidad)
from ventas v, proyecto j
where v.codpj=j.codpj
group by v.codpro, j.nompj, v.codpj;
--Es correcta
select v.codpro, v.codpj, j.nompj, avg(v.cantidad)
from ventas v, proyecto j
where v.codpj=j.codpj
group by v.codpro, v.codpj, j.nompj;
--Muestra lo mismo (pero cambia el orden)

/*Hay que agrupar por cod de proyecto antes que por nombre porque
el código es único pero el nombre no tiene por qué serlo*/
--DUDAAAAAAAAAAAAAA 

/*Ejer 3.35 Mostrar los nombres de proveedores tales que el total de sus ventas superen
la cantidad de 1000 unidades*/
/*Mostrar los nombres de proveedores tales que el total de sus ventas superen
la cantidad de 1000 unidades*/
select pj.nompj
from ventas v, proyecto pj
where v.codpj=pj.codpj
group by pj.codpj, pj.nompj
having sum(v.cantidad)>1000;

--3.6.3 Subconsultas en la cláusula HAVING
/*Ejer 3.36: Mostrar la pieza que más se ha vendido en total*/
select codpie, sum(cantidad)
from ventas
group by codpie
having sum(cantidad) = (select max(sum (cantidad))
                        from ventas v
                        group by codpie);

-- 3.7 Consultas adicionales
-- 3.7.1 Consultas con el tipo DATE
/*Ejerc 3.37 Comprueba que no funciona correctamente si las comparaciones de fechas se
hacen con cadenas*/
SELECT * FROM ventas
WHERE fecha BETWEEN TO_DATE('01/01/2002','DD/MM/YYYY') AND
TO_DATE('31/12/2004','DD/MM/YYYY');
--
SELECT * FROM ventas
WHERE fecha BETWEEN '01/01/2002' AND '31/12/2004';
--sí que funciona

SELECT * FROM ventas
WHERE to_char(fecha) BETWEEN '01/01/2002' AND '31/12/2004';
--no funciona

/*Ejer 3.38 Encontrar la cantidad media de piezas suministradas cada mes*/
select to_char (fecha, 'mm/yyyy'), avg(cantidad)
from ventas
group by to_char(fecha, 'mm/yyyy');

--3.7.2 Otras consultas sobre el catálogo

/*Ejer 3.39 ¿Cuál es el nombre de la vista que tienes que consultar y 
qué campos te pueden interesar?*/
describe dictionary;
--dejo este ejer sin terminar

/*Ejer 3.40 Muestra las tablas ventas a las que tienes acceso de consulta junto con el
nombre del propietario y su número de identificación en el sistema.*/
select i.table_name, u.username, u.user_id
from user_indexes i, all_users u
where (i.table_owner = u.user_id) and (lower(i.table_name) like '%ventas%');
--no compila ns pq

/*Ejer 3.41 Muestra todos tus objetos creados en
el sistema. ¿Hay algo más que tablas?*/
select * from dictionary;

--3.7.3 Ejercicios adicionales
/*Ejer 3.42 Mostrar los códigos de aquellos proveedores que hayan superado 
las ventas totales realizadas por el proveedor ’S1’*/
select codpro, sum(cantidad)
from ventas
group by codpro
having sum(cantidad) > (select sum(cantidad)
                        from ventas v
                        where v.codpro='S1');

/*Ejer 3.43 Mostrar los mejores proveedores, entendiéndose como los que tienen mayores
cantidades totales*/
select codpro, sum(cantidad)
from ventas
group by codpro
having sum(cantidad) = (select max(sum(cantidad))
                        from ventas v
                        group by v.codpro);
                        
/*Ejer 3.44 Mostrar los proveedores que venden piezas a todas las ciudades de los
proyectos a los que suministra ’S3’, sin incluirlo*/
(select codpro 
from proveedor
where codpro!='S3')
minus
(select codpro
from ((select pro.codpro, pj.ciudad
      from proveedor pro, proyecto pj
      where pj.codpj in (select codpj from ventas v where codpro='S3'))
      minus
      (select codpro, pj2.ciudad
      from ventas, proyecto pj2
      where ventas.codpj=pj2.codpj))
);

/*Ejer 3.45 Encontrar aquellos proveedores que hayan 
hecho al menos diez pedidos*/
select codpro, count(codpro)
from ventas
group by codpro
having count(codpro) >= 10;

/*Ejer 3.46 Encontrar aquellos proveedores que venden todas 
las piezas suministradas por S1*/
(select codpro
from proveedor)
minus
(select codpro
from ((select codpro, codpie
      from proveedor, pieza
      where codpie in (select codpie from ventas 
                       where codpro='S1'))
      minus
      (select codpro, codpie
      from ventas))
);

/*Ejer 3.47 Encontrar la cantidad total de piezas que ha 
vendido cada proveedor que cumple la condición de vender 
todas las piezas suministradas por S1*/
select v.codpro, sum(cantidad)
from ventas v
where v.codpro in
((select codpro
from proveedor)
minus
(select codpro
from ((select codpro, codpie
      from proveedor, pieza
      where codpie in (select codpie from ventas 
                       where codpro='S1'))
      minus
      (select codpro, codpie
      from ventas))
))
group by v.codpro;

/*Ejer 3.48 Encontrar qué proyectos están suministrados por 
todos los proveedores que suministran la pieza P3*/
(select codpj
from proyecto)
minus
(select codpj
from ((select codpj, codpro
       from proyecto, proveedor
       where codpro in (select codpro from ventas
                        where codpie='P3'))
        minus
        (select codpj, codpro
        from ventas))
);

/*Ejer 3.49 Encontrar la cantidad media de piezas suministrada
a aquellos proveedores que venden la pieza P3*/
select avg(cantidad)
from ventas
where codpie='P3';
--no me cuadra la psoposición 'a' en el enunciado

/*Ejer 3.50 Queremos saber los nombres de tus índices y sobre 
qué tablas están montados, indica además su propietario*/
 SELECT index_name, table_name, table_owner
 FROM user_indexes;
 
/*Ejer 3.51 Implementar el comando DESCRIBE para tu tabla 
ventas a través de una consulta a las vistas del catálogo*/
select * from user_indexes;
--no me deja mostrar índices asiq ns muy bien cómo hacerlo

/*Ejer 3.52 Mostrar para cada proveedor la media de productos
suministrados cada año*/
select codpro, to_char(fecha, 'yyyy'), avg(cantidad)
from ventas
group by codpro, to_char(fecha, 'yyyy');

/*Ejer 3.53 Encontrar todos los proveedores que venden una pieza roja*/
select codpro
from ventas natural join pieza
where color='Rojo';

/*Ejer 3.54 Encontrar todos los proveedores que venden todas 
las piezas rojas*/
(select codpro
from proveedor)
minus
(select codpro
from ((select codpro, codpie
       from proveedor, pieza
       where color='Rojo')
       minus
       (select codpro, codpie
       from ventas))
);

/*Ejer 3.55 Encontrar todos los proveedores tales que 
todas las piezas que venden son rojas.*/
(select codpro
from proveedor)
minus
(select codpro
from ventas natural join pieza
where color!='Rojo');

/*Ejer 3.56 Encontrar el nombre de aquellos proveedores 
que venden más de una pieza roja*/
select codpro, count(*)
from (select * from ventas natural join pieza
      where color='Rojo')
group by codpro
having count(*)>1;

/*Ejercicio 3.57 Encontrar todos los proveedores que vendiendo 
todas las piezas rojas cumplen la condición de que todas 
sus ventas son de más de 10 unidades*/
((select codpro
from proveedor)
minus -- no venden más de 10 ud
(select codpro
from ventas
where cantidad<=10))
minus --no venden todas las piezas rojas
(select codpro
from ((select codpro, codpie
      from proveedor, pieza
      where color='Rojo')
      minus
      (select codpro, codpie
      from ventas))
);

--otra aproximacion
select codpro
from proveedor
where codpro not in (select codpro
                from ((select codpro, codpie
                      from proveedor, pieza
                      where color='Rojo')
                      minus
                      (select codpro, codpie
                      from ventas))
                )
        and codpro not in (select codpro from ventas
                    where cantidad<=10)
;


/*Ejer 3.58 Coloca el status igual a 1 a aquellos proveedores 
que solo suministran la pieza P1*/
update proveedor
set status=1
where codpro in ((select codpro
                  from proveedor)
                  minus
                 (select codpro
                 from ventas
                 where codpie!='P1'));
                 
select * from proveedor;
commit;

/*Ejer 3.59 Encuentra, de entre las piezas que no se han 
vendido en septiembre de 2009, las ciudades de aquéllas que se 
han vendido en mayor cantidad durante Agosto de ese mismo año*/
select codpie, ciudad, sum(cantidad)
from ventas natural join ((select codpie from pieza)
    minus
    (select codpie from ventas
    where to_char(fecha, 'MM/YYYY')='09/2009'))
    natural join pieza
    where to_char(fecha, 'MM/YYYY')='08/2009'
    group by codpie, ciudad
    having sum(cantidad) = (select max(sum(cantidad))
                            from ventas natural join 
                                ((select codpie from pieza)
                                   minus
                                  (select codpie from ventas
                                   where to_char(fecha)='09/2009'))
                                   natural join pieza
                            where to_char(fecha, 'MM/YYYY')='08/2009'
                            group by codpie, ciudad);

--3.8 Ejercicios adicionales
--3.8.1 Realización de consultas sin operadores de agregación
/*Ejer 3.60 Muestra la información disponible acerca de 
los encuentros de liga*/
select * from encuentro;

/*Ejer 3.61 Muestra los nombres de los equipos y de los
jugadores ordenados alfabéticamente*/
select nombree, nombrej
from equipo natural join jugador
order by nombree, nombrej asc;

/*Ejer 3.62 Muestra los jugadores que no tienen ninguna falta*/
(select codj
from jugador)
minus
(select distinct codj
from faltas);

/*Ejer 3.63 Muestra los compañeros de equipo del jugador que 
tiene por código x (codJ=’x’) y donde x es uno elegido por 
ti*/
select codj
from jugador
where code in (select code from jugador where codj='J11');

/*Ejer 3.64 Muestra los jugadores y la localidad donde juegan
(la de sus equipos)*/
select codj, localidad
from jugador natural join equipo;

/*Ejer 3.65 Muestra todos los encuentros posibles de la liga*/
select e1.code, e2.code
from equipo e1, equipo e2
where e1.code!=e2.code;

/*Ejer 3.66 Muestra los equipos que han ganado algún encuentro
jugando como local*/
select distinct elocal
from encuentro
where plocal>pvisitante;

/*Ejer 3.67 Muestra los equipos que han ganado algún encuentro*/
(select elocal
from encuentro
where plocal>pvisitante)
union
(select evisitante
from encuentro
where plocal<pvisitante);

/*Ejer 3.68 Muestra los equipos que todos los encuentros que 
han ganado lo han hecho como equipo local*/
(select elocal
from encuentro
where plocal>pvisitante)
minus
(select evisitante
from encuentro
where plocal<pvisitante);

/*Ejer 3.69 Muestra los equipos que han ganado todos los 
encuentros jugando como equipo local*/
(select code
from equipo)
minus 
(select elocal
from encuentro
where plocal<pvisitante);

/*Ejer 3.70 Muestra los encuentros que faltan para terminar la
liga. Suponiendo que en la tabla Encuentros solo se almacenan
los encuentros celebrados hasta la fecha*/
(select e1.code, e2.code
from equipo e1, equipo e2
where e1.code!=e2.code)
minus
(select elocal, evisitante
from encuentro);

/*Ejer 3.71 Muestra los encuentros que tienen lugar en la 
misma localidad*/
describe encuentro;

select elocal, evisitante, fecha, plocal, pvisitante
from encuentro, equipo e1, equipo e2
where (elocal=e1.code) and (evisitante=e2.code) and 
(e1.localidad=e2.localidad);

--3.8.2 Realización de consultas con operadores de agregación
/*Ejer 3.72 Para cada equipo, muestra cantidad de encuentros 
que ha disputado como local*/
select elocal, count(*)
from encuentro
group by elocal;

/*Ejer 3.73 Muestra los encuentros en los que se alcanzó
mayor diferencia*/
select elocal, evisitante
from encuentro
group by elocal, evisitante, plocal, pvisitante
having abs(plocal-pvisitante) = (select max(abs(plocal-pvisitante))
                                 from encuentro);
                               
/*Ejer 3.74 Muestra los jugadores que no han superado 3 
faltas acumuladas*/

(select codj from jugador)
minus
(select codj from faltas
group by codj having sum(num)>3);

-- si queremos mostrar las faltas asociadas

describe faltas;
insert into faltas (codj, elocal, evisitante, num) values ('J11', 'E1', 'E2', 5);
insert into faltas (codj, elocal, evisitante, num) values ('J21', 'E1', 'E2', 5);
insert into faltas (codj, elocal, evisitante, num) values ('J31', 'E1', 'E3', 2);

select * from faltas;

select codj cod, suma
from 
        ((select codj from jugador)
        minus
        (select codj from faltas
        group by codj having sum(num)>3))
        natural join
        (select codj, sum(num) suma
        from faltas
        group by codj)
     ;

select codj, sum(num)
from jugador natural join faltas
group by codj
having sum(num)<=3;

--si hay 0 faltas no se puede enseñar :(

/*Ejer 3.75 Muestra los equipos con mayores puntuaciones en 
los partidos jugados fuera de casa*/
select evisitante, pvisitante
from encuentro
group by evisitante, pvisitante
having pvisitante = (select max(pvisitante) from encuentro);

select evisitante, pvisitante
from encuentro
where pvisitante = (select max(pvisitante) from encuentro);

/*Ejer 3.76 Muestra la cantidad de victorias de cada equipo,
jugando como local o como visitante*/
select code, count(*)
from ((select code
       from encuentro, equipo
       where (code=elocal) and (plocal>pvisitante))
       union all
       (select code
       from encuentro, equipo
       where (code=evisitante) and (plocal<pvisitante))) 
group by code;

/*Ejer 3.77 Muestra el equipo con mayor número de victorias*/
select code, count(*)
from ((select code
       from encuentro, equipo
       where (code=elocal) and (plocal>pvisitante))
       union all
       (select code
       from encuentro, equipo
       where (code=evisitante) and (plocal<pvisitante))) 
group by code
having count(*)= (select max(count(*)) 
                  from ((select code
                  from encuentro, equipo
                  where (code=elocal) and (plocal>pvisitante))
                  union all
                  (select code
                  from encuentro, equipo
                  where (code=evisitante) and (plocal<pvisitante))) 
                  group by code
);

/*Ejer 3.78 Muestra el promedio de puntos por equipo en los 
encuentros de ida*/
select evisitante, avg(pvisitante)
from encuentro
group by evisitante;

/*Ejer 3.79 Muestra el equipo con mayor número de puntos en 
total de los encuentros jugados*/

--primera aproximación
select code, sum(p1)
from ((select code, sum(plocal) p1
      from encuentro, equipo
      where code=elocal
      group by code) union all
      (select code, sum(pvisitante) 
      from encuentro, equipo
      where code=evisitante
      group by code))
group by code
having sum(p1) = (select max(sum(p2))
                    from ((select e2.code, sum(e1.plocal) p2
                        from encuentro e1, equipo e2
                        where e2.code=e1.elocal
                        group by e2.code) 
                    union all
                        (select e4.code, sum(e3.pvisitante) 
                        from encuentro e3, equipo e4
                        where e4.code=e3.evisitante
                        group by e4.code))
                    group by code);
                    
--segunda aproximación
select cod, sum(punt)
from ((select elocal cod, plocal punt
        from encuentro)
        union all
        (select evisitante, pvisitante
        from encuentro))
group by cod
having sum(punt) = (select max(sum(punt))
                    from ((select elocal cod, plocal punt
                            from encuentro)
                            union all
                            (select evisitante, pvisitante
                            from encuentro))
                    group by cod);


/*
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
--------- SESIÓN 4 -----------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
*/

/*Ejer 4.1 Crear una vista con los proveedores de Londres. ¿Qué sucede si insertamos
en dicha vista la tupla (’S7’,’Jose Suarez’,3,’Granada’)?. (Buscar en [4] la cláusula
WITH CHECK OPTION ).*/
describe proveedor;

create view ProLondres (codpro, nompro, status) as
    select codpro, nompro, status
    from proveedor
    where ciudad='Londres';

create or replace view ProLondres (codpro, nompro, status, ciudad) as
    select codpro, nompro, status, ciudad
    from proveedor
    where ciudad='Londres';

select * from prolondres;

insert into prolondres 
values ('S8','Jose Suarez',3,'Granada');
-- se inserta en ventproveedoras, y como la comprobacion
-- de ciudad sale falsa, no se mete en la vista
-- no permite S7 pq ya existe en ventas

/*Ejer 4.2 Crear una vista con los nombres de los proveedores y sus ciudades. Inserta
sobre ella una fila y explica cuál es el problema que se plantea. ¿Habría problemas de
actualización?*/

create view ProvNomCiu (nompro, ciudad) as
select nompro, ciudad
from proveedor;

select * from provnomciu;

insert into provnomciu values ('Maria Ruiz', 'Ubeda');
-- no me deja pq no puede meter nada en ventas!!

/*Ejer 4.3 Crear una vista donde aparezcan el código de proveedor, el nombre de proveedor y el código del proyecto tales que la pieza sumistrada sea gris. Sobre esta vista realiza
alguna consulta y enumera todos los motivos por los que sería imposible realizar una inserción*/

create view mezcla (codpro, nompro, codpj) as
select codpro, nompro, codpj
from ventas 
     natural join 
     (select codpie
      from pieza
      where color='Rojo')
      natural join
      proveedor
;

select * from mezcla;

--imposible hacer ninguna insercion pq falta la 
--componente de la clave primaria de ventas codpie!!

commit;

/*
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
--------- SESIÓN 5 -----------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
*/

/*Ejer 5.1 Ver la descripción de la vista del catálogo USER_TABLES.*/
describe user_tables;

/*Ejer 5.2 Completar la siguiente secuencia */
create table acceso (testigo number);

insert into acceso values(1);
insert into acceso values (2);

grant select on acceso to x5924253;

select * from x5924253.acceso;

revoke select on acceso from x5924253;

select * from x5924253.acceso;

GRANT SELECT ON acceso TO x5924253 WITH GRANT OPTION;

grant select on x5924253.acceso to x3949965;

select * from x5924253.acceso;

revoke select on acceso from x5924253;

-- por terminar
exit;
/*
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
--------- EJERCICIOS ADICIONALES ---------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
*/
/*Ejer 1*/
-- a)  Proveedor que tiene el mayor número de ventas de la pieza P1 en el último 
--    año (puede ser más de uno)

(select distinct codpj
from ventas
where codpie='P1')
minus
(select distinct a1
from (select codpj a1, count(codpj) c1
      from ventas
      where codpie='P1'
      group by codpj),
      (select codpj a2, count(codpj) c2
      from ventas
      where codpie='P1'
      group by codpj)
where c1<c2)
;

-- b) Piezas de color blanco que aparecen en, al menos, tres envíos con 
--   proveedores diferentes

select codpie, count (codpie)
      from (select codpie, codpro
            from ventas)
            natural join
            (select codpie
            from pieza
            where color='Blanco')
      group by codpie
      having count(codpie)>2
;

-- c) Proyectos en los que los suministros en el año 2000 tienen una cantidad 
--   media superior a 150

select codpj, avg(cantidad)
from ventas
where to_char(fecha, 'yyyy')=2000
group by codpj
having avg(cantidad) > 150;

-- d) Proveedores con el número más alto de suministros a proyectos de Londres 
--   realizados durante el mes de enero de 2000
select codpro, count (codpro)
from ventas
     natural join
     (select codpj
      from proyecto
      where ciudad='Londres')
where to_char(fecha, 'mm/yyyy')='01/2000'
group by codpro
having count(codpro) =
(select max (count(codpro))
from ventas
     natural join
     (select codpj
      from proyecto
      where ciudad='Londres')
where to_char(fecha, 'mm/yyyy')='01/2000'
group by codpro);

-- e)Proveedores que han suministrado al menos tres piezas distintas a cada 
--  proyecto 

--primera aprox
/*select codpro
from (select *
      from ventas v1
      where codpro not in (select codpro -- proveedores que han vendido a todos los proyectos
                           from ((select codpj from proyecto),
                                 (select codpro from proveedor)
                                minus
                                 (select codpj, codpro from ventas)))
                           
     ), 
     (select *
      from ventas v2
      where codpro not in (select codpro -- proveedores que han vendido a todos los proyectos
                           from ((select codpj from proyecto),
                                 (select codpro from proveedor)
                                minus
                                 (select codpj, codpro from ventas)))
                           
     ),
     (select *
      from ventas v3
      where codpro not in (select codpro -- proveedores que han vendido a todos los proyectos
                           from ((select codpj from proyecto),
                                 (select codpro from proveedor)
                                minus
                                 (select codpj, codpro from ventas)))
                           
     )
where v1.codpie;*/
                           
(select codpro -- todos los pro que venden
from ventas)
minus -- pro que venden 3 a todos los suyos
select codpro from -- pro que no le vende 3 a todos los suyos
((select codpro, codpj -- pj a los que pro le vende
from ventas)
minus
(select codpro, codpj -- pj a los que pro le vende más de 3 piezas
from ventas 
group by codpro, codpj
having count(codpie)>3));

-- f) Piezas que aparecen en un único suministro durante el año 2010
select codpie
from ventas
where to_char(fecha,'yyyy')='2010'
group by codpie
having count(codpie)=1;

-- g) Piezas cuyo último suministro fue realizado en marzo de 2010

(select codpie
from ventas
where to_char(fecha,'mm/yyyy')='03/2010')
minus
(select codpie
from ventas
where to_char(fecha,'mm/yyyy')>'03/2010');

-- h) Proyectos que reciben solo tres piezas distintas de proveedores de Londres

select codpj 
from (ventas
      natural join
      (select codpro
       from proveedor
       where ciudad='Londres'))
group by codpj
having count(codpie) = 3;

-- i) Proyectos que sólo tienen un proveedor con varios suministros en el 
--   último año

-- primera aproximacion (pj que tienen prov con varias ventas el ult año)
(select codpj --pj que tienen
from ventas
where codpro in (select codpro --un pro 
                 from ventas
                 where to_char(fecha,'yyyy')='2023'
                 group by codpro --con ventas en el ult año
                 having count(codpro)>1)
)
minus --pj que unicamente tienen pro con ventas en el ult año 
(select codpj --proyectos que tienen
from ventas
where codpro not in (select codpro --un pro que no está
                 from ventas -- en ventas del ult año
                 where to_char(fecha,'yyyy')='2023'
                 group by codpro
                 having count(codpro)>1))
;

--segunda aprox (la buena)
select codpj --proyectos que tienen
from ventas
where codpro in (select codpro --un pro que está
                 from ventas -- en ventas del ult año
                 where to_char(fecha,'yyyy')='2023'
                 group by codpro
                 having count(codpro)>1)
group by codpj
having count(codpro)=1; -- y tienen un unico pro


-- j) Piezas de color rojo que han sido suministradas al menos dos veces cada 
--   año (considerando solo los años en los que se han producido envíos en la BD)

--primera aprox: piezas rojas que han sido suministradas cada año
(select distinct codpie
from ventas
     natural join
     (select codpie from pieza where color='Rojo'))
minus
(select codpie
from ((select v.codpie, to_char(f.fecha, 'yyyy')
        from (select distinct codpie from 
             ventas 
             natural join
             (select codpie from pieza where color='Rojo')) v,
             (select distinct fecha
             from ventas) f
     )
     minus
    (select codpie, to_char(fecha, 'yyyy')
    from ventas)
    )
);          


--segunda aprox: piezas rojas que han sido suministradas al menos dos veces cada año
(select distinct codpie
from ventas
     natural join
     (select codpie from pieza where color='Rojo'))
minus
(select codpie
from ((select v.codpie, to_char(f.fecha, 'yyyy')
        from (select distinct codpie from 
             ventas 
             natural join
             (select codpie from pieza where color='Rojo')) v,
             (select distinct fecha
             from ventas) f
     )
     minus
    (select codpie, to_char(fecha, 'yyyy')
    from ventas
    group by codpie, to_char(fecha, 'yyyy')
    having count(codpie)>1)
    )
);

/*Ejer 2*/
-- a) Proponga y resuelva una consulta original de división simple
-- Encontrar aquellos moviles que hayan iniciado una llamada con cualquier fijo

(select numero
from movil)
minus
(select m
 from ((select movil.numero m, fijo.numero
       from movil, fijo)
       minus
       (select num_orig, num_dest
       from llama) --si hay un par fijo,fijo no pasa nada
       )
);

-- b) Proponga y resuelva una consulta original de división que imponga 
--   restricciones a los candidatos

-- Encontrar aquellos moviles superiores al 656789223 que 
-- hayan iniciado una llamada con cualquier fijo

(select numero
from movil
where numero>656789223)
minus
(select m
 from ((select movil.numero m, fijo.numero
       from movil, fijo
       where movil.numero>656789223)
       minus
       (select num_orig, num_dest
       from llama) --si hay un par fijo,fijo no pasa nada
       )
);

-- c) Proponga y resuelva una consulta original de división que imponga 
--   restricciones en el divisor

-- Encontrar aquellos moviles que hayan iniciado una llamada con cualquier 
-- fijo superior 925770247

(select numero
from movil)
minus
(select m
 from ((select movil.numero m, fijo.numero
       from movil, fijo
       where fijo.numero>925770247)
       minus
       (select num_orig, num_dest
       from llama) --si hay un par fijo,fijo no pasa nada
       )
);


-- d) Proponga y resuelva una consulta original de división que imponga 
--   restricciones sobre la forma de relacionarse con los elementos del divisor

por hacer;


/*Ejer 3 Escriba las sentencias de creación de tablas para cada uno de los esquemas 
de los ejercicios en los que hemos trabajado en clase.  Imponga las 
restricciones que considere oportuno y justifique el motivo. */

-- Ejer 8 seminario 2 (piezas)

create table pieza1
( cod VARCHAR2(5) constraint cod_pk primary key,
  denominacion VARCHAR(10)
);

create table piesimple
( cod constraint cod_fk references pieza1(cod) primary key,
  precio NUMBER
);

create table piecompuesta
( cod constraint cod_fk2 references pieza1(cod) primary key,
  precioc NUMBER
);

create table compuesta_de
( cod_todo constraint cod_fk3 references piecompuesta(cod),
  cod_parte constraint cod_fk4 references pieza1(cod),
  cantidad NUMBER,
  constraint pk primary key (cod_todo, cod_parte)
);

-- Ejer 10 seminario 2 (llamadas)

create table telefono
( numero NUMBER primary key,
   check (numero>=111111111 and numero<=999999999)
);

create table fijo
( numero references telefono(numero) primary key
);

create table movil
( numero references telefono(numero) primary key
);

create table llama 
( num_orig references telefono(numero),
  num_dest references telefono(numero) not null,
  inicio date not null,
  fin date,
  primary key (num_orig, inicio),
  unique (num_orig, fin),
  unique (num_dest, inicio),
  unique (num_dest, fin)
);
  
  
exit;






                                                        
                                        
                             



