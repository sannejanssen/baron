<?php

/**
 * @file
 * Implementation for the main pages.
 */

// Plugin definition
$plugin = array(
  'title' => t('One col two rows'),
  'category' => t('Baron'),
  'theme' => 'tworows',
  'icon' => 'main.png',
  'css' => 'tworows.css',
  'regions' => array(
    'row_one' => t('Row One'),
    'row_two' => t('Row Two'),
  ),
);
