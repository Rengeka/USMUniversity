<?php
/*
Plugin Name: USM Notes
Description: Плагин для заметок с приоритетами и датой напоминания
Version: 1.0
Author: Stanislav Ciobanu
*/

if (!defined('ABSPATH')) exit;


/**
 * =========================
 * ШАГ 3: CPT "Заметки"
 * =========================
 */
function usm_register_notes_cpt() {
    $labels = array(
        'name' => 'Заметки',
        'singular_name' => 'Заметка',
        'add_new' => 'Добавить',
        'add_new_item' => 'Добавить заметку',
        'edit_item' => 'Редактировать заметку',
        'new_item' => 'Новая заметка',
        'view_item' => 'Просмотр заметки',
        'search_items' => 'Поиск заметок',
        'not_found' => 'Заметки не найдены',
    );

    register_post_type('usm_note', array(
        'labels' => $labels,
        'public' => true,
        'has_archive' => true,
        'menu_icon' => 'dashicons-welcome-write-blog',
        'supports' => array('title', 'editor', 'author', 'thumbnail'),
    ));
}
add_action('init', 'usm_register_notes_cpt');

/**
 * =========================
 * ШАГ 4: Таксономия "Приоритет"
 * =========================
 */
function usm_register_priority_taxonomy() {
    $labels = array(
        'name' => 'Приоритеты',
        'singular_name' => 'Приоритет',
        'search_items' => 'Поиск приоритетов',
        'all_items' => 'Все приоритеты',
        'edit_item' => 'Редактировать приоритет',
        'add_new_item' => 'Добавить приоритет',
    );

    register_taxonomy('usm_priority', 'usm_note', array(
        'labels' => $labels,
        'hierarchical' => true,
        'public' => true,
    ));
}
add_action('init', 'usm_register_priority_taxonomy');

/**
 * =========================
 * ШАГ 5: Метабокс даты
 * =========================
 */

// Добавление метабокса
function usm_add_meta_box() {
    add_meta_box(
        'usm_reminder_date',
        'Дата напоминания',
        'usm_meta_box_callback',
        'usm_note'
    );
}
add_action('add_meta_boxes', 'usm_add_meta_box');

// HTML метабокса
function usm_meta_box_callback($post) {
    wp_nonce_field('usm_save_meta', 'usm_meta_nonce');

    $value = get_post_meta($post->ID, '_usm_reminder_date', true);

    echo '<label>Выберите дату:</label><br>';
    echo '<input type="date" name="usm_reminder_date" value="' . esc_attr($value) . '" required>';
}

// Сохранение
function usm_save_meta($post_id) {

    if (!isset($_POST['usm_meta_nonce']) ||
        !wp_verify_nonce($_POST['usm_meta_nonce'], 'usm_save_meta')) {
        return;
    }

    if (defined('DOING_AUTOSAVE') && DOING_AUTOSAVE) return;

    if (isset($_POST['usm_reminder_date'])) {

        $date = $_POST['usm_reminder_date'];
        $today = date('Y-m-d');

        // Проверка: дата обязательна
        if (empty($date)) {
            wp_die('Дата обязательна');
        }

        // Проверка: не в прошлом
        if ($date < $today) {
            wp_die('Дата не может быть в прошлом');
        }

        update_post_meta($post_id, '_usm_reminder_date', sanitize_text_field($date));
    }
}
add_action('save_post', 'usm_save_meta');

/**
 * Отображение даты в админке
 */
function usm_add_column($columns) {
    $columns['reminder_date'] = 'Дата напоминания';
    return $columns;
}
add_filter('manage_usm_note_posts_columns', 'usm_add_column');

function usm_show_column($column, $post_id) {
    if ($column == 'reminder_date') {
        echo esc_html(get_post_meta($post_id, '_usm_reminder_date', true));
    }
}
add_action('manage_usm_note_posts_custom_column', 'usm_show_column', 10, 2);

/**
 * =========================
 * ШАГ 6: Шорткод
 * =========================
 */
function usm_notes_shortcode($atts) {

    $atts = shortcode_atts(array(
        'priority' => '',
        'before_date' => ''
    ), $atts);

    $args = array(
        'post_type' => 'usm_note',
        'posts_per_page' => -1,
    );

    // Фильтр по приоритету
    if (!empty($atts['priority'])) {
        $args['tax_query'] = array(
            array(
                'taxonomy' => 'usm_priority',
                'field' => 'slug',
                'terms' => $atts['priority'],
            )
        );
    }

    // Фильтр по дате
    if (!empty($atts['before_date'])) {
        $args['meta_query'] = array(
            array(
                'key' => '_usm_reminder_date',
                'value' => $atts['before_date'],
                'compare' => '<=',
                'type' => 'DATE'
            )
        );
    }

    $query = new WP_Query($args);

    ob_start();

    echo '<div class="usm-notes">';

    if ($query->have_posts()) {
        while ($query->have_posts()) {
            $query->the_post();

            $date = get_post_meta(get_the_ID(), '_usm_reminder_date', true);

            echo '<div class="usm-note">';
            echo '<h3>' . get_the_title() . '</h3>';
            echo '<p>' . get_the_content() . '</p>';
            echo '<small>Дата: ' . esc_html($date) . '</small>';
            echo '</div>';
        }
    } else {
        echo '<p>Нет заметок с заданными параметрами</p>';
    }

    echo '</div>';

    wp_reset_postdata();

    return ob_get_clean();
}
add_shortcode('usm_notes', 'usm_notes_shortcode');

/**
 * =========================
 * Стили
 * =========================
 */
function usm_notes_styles() {
    echo '
    <style>
        .usm-note {
            border: 1px solid #ddd;
            padding: 10px;
            margin-bottom: 10px;
            border-radius: 5px;
        }
        .usm-note h3 {
            margin: 0 0 5px;
        }
    </style>
    ';
}
add_action('wp_head', 'usm_notes_styles');