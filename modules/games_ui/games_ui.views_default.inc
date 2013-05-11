<?php

/**
 * Implements hook_views_default_views().
 */
function games_ui_views_default_views() {
 $view = new view();
$view->name = 'games';
$view->description = 'This is the list of game that are already playable by your system';
$view->tag = 'default';
$view->base_table = 'game';
$view->human_name = 'Games';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Games';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<a href=/game/add>Create New Game</a>';
$handler->display->display_options['header']['area']['format'] = 'full_html';
/* Field: Game: Game ID */
$handler->display->display_options['fields']['gid']['id'] = 'gid';
$handler->display->display_options['fields']['gid']['table'] = 'game';
$handler->display->display_options['fields']['gid']['field'] = 'gid';
$handler->display->display_options['fields']['gid']['label'] = '';
$handler->display->display_options['fields']['gid']['exclude'] = TRUE;
$handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gid']['element_default_classes'] = FALSE;
/* Field: Game: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'game';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['path'] = 'game/[gid]';
/* Field: Game: Description */
$handler->display->display_options['fields']['description']['id'] = 'description';
$handler->display->display_options['fields']['description']['table'] = 'game';
$handler->display->display_options['fields']['description']['field'] = 'description';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Edit';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Edit';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'game/[gid]/edit';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing1']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing1']['table'] = 'views';
$handler->display->display_options['fields']['nothing1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing1']['label'] = 'Play';
$handler->display->display_options['fields']['nothing1']['alter']['text'] = 'Play';
$handler->display->display_options['fields']['nothing1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing1']['alter']['path'] = 'game/[gid]/play';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'games';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Games';
$handler->display->display_options['menu']['weight'] = '0';




  $views['games'] = $view;

  return $views;
}
