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