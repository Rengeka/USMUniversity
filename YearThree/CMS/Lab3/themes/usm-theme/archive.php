<?php get_header(); ?>

<div class="content">

    <h2>Архив</h2>

    <?php if (have_posts()) : ?>
        <?php while (have_posts()) : the_post(); ?>
            <h3>
                <a href="<?php the_permalink(); ?>">
                    <?php the_title(); ?>
                </a>
            </h3>
        <?php endwhile; ?>
    <?php else : ?>
        <p>Ничего не найдено</p>
    <?php endif; ?>

</div>

<?php get_sidebar(); ?>
<?php get_footer(); ?>