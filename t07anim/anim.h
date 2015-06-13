/* FILENAME: ANIM.H
 * PROGRAMMER: dk6
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "vec.h"

/* Максимальное количество элементов анимации */
#define dk6_MAX_UNITS 3000

/* Объявление типа объектов анимации "вперед" */
typedef struct tagdk6UNIT dk6UNIT;

/* Структура хранения контекста анимации */
typedef struct
{
  HWND hWnd;          /* Окно вывода */
  INT W, H;           /* Размер окна вывода */
  HDC hDC;            /* Контекст вывода окна */
  HGLRC hGLRC;        /* Контекст рендеринга */

  /* Массив элементов анимации и их количество */
  dk6UNIT *Units[dk6_MAX_UNITS]; 
  INT NumOfUnits;

  /* Подсистема синхронизации */
  DBL
    Time,            /* время в секундах со старта анимации */
    GlobalTime,      /* время -"-, но без паузы */
    DeltaTime,       /* межкадровое время в секундах */
    GlobalDeltaTime, /* межкадровое время в секундах без паузы */
    FPS;             /* количество кадров в секунду */
  BOOL
    IsPause;         /* флаг паузы */

  /* Подсистема ввода */
  BYTE
    Keys[256],       /* Сотояние клавиш клавиатуры и мыши */
    KeysOld[256],    /* Сотояние клавиш на предыдущем кадре */
    KeysClick[256];  /* Флаги однократного нажатия */
  INT
    MsDeltaX, MsDeltaY, /* Относительные координаты курсора мыши */
    MsX, MsY,        /* Абсолютные координаты курсора мыши */
    MsWheel;         /* Состояние колеса мыши */
  BYTE
    JButs[32],       /* Сотояние кнопок джойстика */
    JButsOld[32],    /* Сотояние кнопок джойстика на предыдущем кадре */
    JButsClick[32],  /* Флаги однократного нажатия кнопок джойстика */
    JPOV;            /* Переключатель POV - 0..8 */
  DBL
    JX, JY, JZ, JR, JU, JV; /* Оси джойстика (-1.0 .. 1.0*/

  VEC PosModel;
  DBL AngleX, AngleY, AngleZ;
} dk6ANIM;

/* Глобальная переменная - счетчик прокрутки колеса мыши */
extern INT dk6_MouseWheel;

/* Системный контекст анимации */
extern dk6ANIM dk6_Anim;

/* Базовые поля объекта анимации:
 * - размер структуры для наследования
 *     INT Size;
 * - идентификатор объеткта:
 *     INT Id;
 * - указатель на функцию инициализации
 *     VOID (*Init)( dk6UNIT *Unit, dk6ANIM *Ani );
 * - указатель на функцию деинициализации
 *     VOID (*Close)( dk6UNIT *Unit, dk6ANIM *Ani );
 * - указатель на функцию обновления межкадровых параметров
 *     VOID (*Response)( dk6UNIT *Unit, dk6ANIM *Ani );
 * - указатель на функцию построения
 *     VOID (*Render)( dk6UNIT *Unit, dk6ANIM *Ani );
 */
#define dk6_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( dk6UNIT *Unit, dk6ANIM *Ani );       \
  VOID (*Close)( dk6UNIT *Unit, dk6ANIM *Ani );      \
  VOID (*Response)( dk6UNIT *Unit, dk6ANIM *Ani );   \
  VOID (*Render)( dk6UNIT *Unit, dk6ANIM *Ani )

/* Базовый тип объекта анимации */
struct tagdk6UNIT
{
  dk6_UNIT_BASE_FIELDS;
};

/* Функция инициализации анимации.
 * АРГУМЕНТЫ:
 *   - дескриптор окна:
 *       HWND hWnd;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
BOOL dk6_AnimInit( HWND hWnd );

/* Функция деинициализации анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimClose( VOID );

/* Функция обработки изменения размера области вывода.
 * АРГУМЕНТЫ:
 *   - новый размер области вывода:
 *       INT W, H;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimResize( INT W, INT H );

/* Функция построения кадра анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimRender( VOID );

/* Функция вывода кадра анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimCopyFrame( VOID );

/* Функция добавления в систему объекта анимации.
 * АРГУМЕНТЫ:
 *   - добавляемый объект анимации:
 *       dk6UNIT *Unit;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimAddUnit( dk6UNIT *Unit );

/* Функция переключения в/из полноэкранного режима
 * с учетом нескольких мониторов.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimFlipFullScreen( VOID );

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (dk6UNIT *) указатель на созданный объект анимации.
 */
dk6UNIT * dk6_AnimUnitCreate( INT Size );

/* Функция выхода из анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimDoExit( VOID );

/* Функция установки паузы анимации.
 * АРГУМЕНТЫ:
 *   - флаг паузы:
 *       BOOL NewPauseFlag;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID dk6_AnimSetPause( BOOL NewPauseFlag );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */