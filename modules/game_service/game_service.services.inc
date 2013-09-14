<?php
function game_service_default_services_endpoint() {
  $export = array();

    $endpoint = new stdClass();
    $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
    $endpoint->api_version = 3;
    $endpoint->name = 'games';
    $endpoint->server = 'rest_server';
    $endpoint->path = 'gameis';
    $endpoint->authentication = array(
      'services' => 'services',
    );
    $endpoint->server_settings = array();
    $endpoint->resources = array(
      'game' => array(
        'operations' => array(
          'create' => array(
            'enabled' => '1',
          ),
          'retrieve' => array(
            'enabled' => '1',
          ),
          'update' => array(
            'enabled' => '1',
          ),
          'delete' => array(
            'enabled' => '1',
          ),
          'index' => array(
            'enabled' => '1',
          ),
        ),
      ),
      'running_game' => array(
        'operations' => array(
          'retrieve' => array(
            'enabled' => '1',
          ),
          'index' => array(
            'enabled' => '1',
          ),
        ),
      ),
    );
    $endpoint->debug = 1;

  $export['games'] = $endpoint;

  return $export;
}