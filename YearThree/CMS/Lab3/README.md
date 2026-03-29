# Lab 3

## Цель работы 

Научиться создавать собственную тему WordPress, разобраться в её минимальной структуре и принципах работы шаблонов.

## Создание темы

Примонтируем директорию ```./themes``` к ```/var/www/html/wp-content/themes```

Создадим директорию ```usm-theme``` в папке ```/var/www/html/wp-content/themes```

### styles.css
Создадим .css файл с данными стилей.

### index.php
Создадим основной .php файл.

```php
<?php get_header(); ?>

<div class="content">

    <h2>Последние публикации</h2>

    <?php if (have_posts()) : ?>
        <?php while (have_posts()) : the_post(); ?>
            <article>
                <h3>
                    <a href="<?php the_permalink(); ?>">
                        <?php the_title(); ?>
                    </a>
                </h3>

                <small>Опубликовано: <?php the_date(); ?></small>

                <p><?php the_excerpt(); ?></p>
            </article>
        <?php endwhile; ?>
    <?php else : ?>
        <p>Записей нет.</p>
    <?php endif; ?>

</div>

<?php get_sidebar(); ?>
<?php get_footer(); ?>
```

### Другие .php
Так же создадим archive.php, comments.php, footer.php, functions.php, header.php, page.php, sidebar.php, single.php.

### Результат
![1](images/1.png)

## Контрольные вопросы

Какие два файла являются обязательными для любой темы WordPress?

    style.css — содержит метаданные темы (без него тема не распознается)

    index.php — основной шаблон (fallback, если нет других файлов)

Как подключаются общие части шаблонов (header, footer, sidebar)?

    С помощью встроенных функций WordPress:
    get_header();
    get_footer();
    get_sidebar();

Чем отличаются index.php, single.php и page.php?

    index.php
    Универсальный шаблон (используется, если нет более подходящего)

    single.php
    Используется для отображения одной записи (post)

    page.php
    Используется для отображения страниц (page)

Зачем нужен файл functions.php в теме?

    functions.php используется для:

    Подключения стилей и скриптов (wp_enqueue_style, wp_enqueue_script)
    Добавления функций темы
    Регистрации меню, сайдбаров, виджетов
    Расширения возможностей темы