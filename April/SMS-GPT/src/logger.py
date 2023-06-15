import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

# Create a console handler
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)

# Create a formatter and add it to the handler
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch.setFormatter(formatter)

# Add the handler to the logger
logger.addHandler(ch)
logger.debug('Debug message')
logger.info('Informational message')
logger.warning('Warning message')
logger.error('Error message')
logger.critical('Critical message')
